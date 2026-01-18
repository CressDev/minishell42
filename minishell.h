/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:25:30 by cress             #+#    #+#             */
/*   Updated: 2026/01/18 14:13:03 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>

# include <errno.h>

# define COLOR_RESET	"\033[0m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_GREEN	"\033[1;32m"

extern int	g_signal;

typedef enum e_state
{
	STATE_START,
	STATE_WORD,
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_PIPE,
	STATE_REDIRECT,
	STATE_ERROR,
	STATE_END,
}	t_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

/**
 * @struct s_fsm
 * @brief Final State Machine that controls the input offered by the user.
 * This analyze the string given of the shell and convert them into tokens,
 * that will be interpreted by the lexer. 
 * 
 * Composition:
 * 
 * - current_state = the state of the FSM at the moment in actual character.
 * 
 * - prev_state = previous state of FSM to control quotes and special status.
 * 
 * - i_token = inner index of the token (buffer control).
 * 
 * - i_input = inner inxed of the input (buffer control).
 * 
 * - i_len = lenght of user input.
 * 
 * - counter = number that represent another value of interest in the FSM.
 * 
 * - has_error = bool to control special error state in FSM.
 * 
 * - has_content = bool to determinate if the token has content.
 * 
 * - input = user entry allocated with readline function
 * 
 * - token = constructed buffer to save the user input. The token is created
 * from it's content.
 */
typedef struct s_fsm
{
	t_state			current_state; /**< Current state of FSM. */
	t_state			prev_state; /**< Previous state of FSM. */
	size_t			i_token; /**< Inner index of buffer. */
	size_t			i_input; /**< Inner state of user input. */
	size_t			i_len; /**< Lenght of the user input. */
	size_t			token_capacity; /**< Int to represet initial buffer size */
	bool			quote_flag; /**< Flag alert for quotes in FSM. */
	bool			has_error; /**< Boolean to control error state. */
	bool			has_content; /**< Boolean for the token creation. */
	char			*input; /**< User input (readline). */
	char			*token; /**< Buffer to construct tokens. */
}	t_fsm;

/**
 * @struct s_envs
 * @brief Represents the environment of the minishell.
 * 
 * Composition:
 * 
 * - env: Linked list of "NAME=VALUE" from the parent process environment.
 *        This is the shell's internal representation and can be modified
 *        (e.g., export, unset, SHLVL).
 * 
 * - environ: Pointer to the original environment (array of strings),
 *            read-only. Represents the environment of the minishell.
 */
typedef struct s_envs
{
	t_list			**env;
	char			**environ;
}	t_envs;

/**
 * @struct s_token
 * @brief Represents the tokens and inner composition for analysis.
 * 
 * Each token can point to the next, contain a text value,
 * a token type (word, pipe, redirection, etc.) and a type of quote.
 * 
 * Composition:
 * 
 * - next = pointer to the next token.
 * 
 * - content = it contains the token string.
 * 
 * - type: (1 = word, 2 = squote, 3 = dquote, etc.).
 * 
 * - quote: type of quote (0 = no quote; 1 = squote; 2 = dquote).
 */
typedef struct s_token
{
	char			*content; /**< Token to be interpreted. */
	int				quote; /**< Quote type. */
	t_token_type	type; /**< Type of the content (determined by enum). */
	struct s_token	*next; /**< Next token. */
}	t_token;

/**
 * @struct s_cmd
 * @brief Represents a single command that has been fully parsed.
 * 
 * This structure encapsulates all the information needed to execute a command,
 * including its arguments, redirections, heredoc delimiters, and links
 * to the next command in a pipeline.
 * 
 * Composition:
 * 
 * - envs: Pointer to the environment structure.
 * 
 * - args: Null-terminated array of strings representing the command.
 *         For example, for `ls -l /tmp`, args = ["ls", "-l", "/tmp", NULL].
 * 
 * - input_file: Path to a file for input redirection (`< filename`).
 *               NULL if no input redirection is specified.
 * 
 * - output_file: Path to a file for output (`> filename` or `>> filename`).
 *                NULL if no output redirection is specified.
 * 
 * - heredoc_delimiter: Array containing the delimiters of heredoc(`<<`).
 *                      Each entry represents a separate heredoc in the command.
 *                      NULL if no heredoc is specified.
 * 
 * - append: Flag indicating the mode of output redirection.
 *           1 if appending to the output file (`>>`), 0 if truncating (`>`).
 * 
 * - is_heredoc: Flag indicating whether the command uses a heredoc (`<<`) input.
 * 
 * - argc: Number of commands stored in args.
 * 
 * - next: Pointer to the next t_cmd in a pipeline sequence.
 *         NULL if this is the last command in the pipeline.
 * 
 * Example usage:
 * 
 * Command: `cat file.txt | grep foo > out.txt`
 * 
 * Parsed structure:
 *   cmd1: args = ["cat", "file.txt", NULL], next -> cmd2
 *   cmd2: args = ["grep", "foo", NULL], 
 * 					output_file = "out.txt", append = 0, next = NULL
 */
typedef struct s_cmd
{
	t_envs			*envs;					/**< Shell environment. */
	char			**args;					/**< Command and arguments. */
	char			*input_file;			/**< Input redirection file. */
	char			*output_file;			/**< Output redirection file. */
	char			**heredoc_delimiter;	/**< Heredoc delimiters. */
	int				append;					/**< Output append flag (>>). */
	int				is_heredoc;				/**< Heredoc flag (<<). */
	int				argc;					/**< Number of commands. */
	struct s_cmd	*next;					/**< Next command in pipeline. */
}	t_cmd;

typedef struct s_exec_data
{
	int				is_tty;
	pid_t			last_child_pid;
}	t_exec_data;

typedef struct s_pipeinfo
{
	int				*prev_fd;
	int				pipefd[2];
}	t_pipeinfo;

bool			handle_eof(char *line, int is_tty);
bool			handle_interrupt(char *line);
bool			obtain_tokens(char *line, t_token **tokens);
void			entry_point(char *input, t_token **tokens);
t_fsm			*init_fsm(char *input);
t_token_type	fsm_state_to_token_type(t_fsm *fsm);
typedef bool	(*t_state_handler)(t_fsm *, char, t_token **);
bool			state_start(t_fsm *fsm, char c, t_token **tokens);
bool			state_word(t_fsm *fsm, char c, t_token **tokens);
bool			state_squote(t_fsm *fsm, char c, t_token **tokens);
bool			state_dquote(t_fsm *fsm, char c, t_token **tokens);
bool			state_pipe(t_fsm *fsm, char c, t_token **tokens);
bool			state_end(t_fsm *fsm, char c, t_token **tokens);
bool			state_redirect(t_fsm *fsm, char c, t_token **tokens);
bool			state_error(t_fsm *fsm, char c, t_token **tokens);
void			error_user_input(t_fsm *fsm, const char *line);
void			default_state(t_fsm *fsm);
void			create_token(t_fsm *fsm, t_token **tokens);

t_token			*init_token(t_fsm *fsm, int quoted);
void			token_append_str(t_fsm *fsm, const char *str, t_token **tokens);
void			token_append_char(t_fsm *fsm, const char c, t_token **tokens);
void			expand_token_buffer(t_fsm *fsm, t_token **tokens);
void			token_add_back(t_token **tokens, t_token *new);
void			free_tokens(t_token **tokens);
t_cmd			*token_word(t_cmd *current, t_token *token, t_envs *envs);
t_cmd			*token_pipe(t_envs *envs, t_cmd *current);
void			token_redirect(t_cmd *current, t_token *token);

t_cmd			*init_cmd(t_envs *envs);
t_cmd			*parse_tokens(t_token *token, t_envs *envs);
void			expand_token(t_token *token, t_envs *envs);
void			restore_fds(int saved_stdin, int saved_stdout, int input_fd,
					int output_fd);
void			execute_redir(t_cmd *cmd, int is_tty);
int				setup_input_redirect(t_cmd *cmd);
int				setup_output_redirect(t_cmd *cmd);
int				setup_all_heredocs(t_cmd *cmd, int is_tty);
void			commands(t_token **tokens, t_envs *envs, int is_tty);

void			close_pipe_child(t_cmd *current, int *prev_fd, int pipefd[2],
					int *out_fd);
void			execute_pipeline(t_cmd *cmd, int is_tty);
void			execute_pipeline_child(t_cmd *cmd, int input_fd, int output_fd,
					t_exec_data *exec_data);
void			setup_pipe_redirections(int input_fd, int output_fd);
void			setup_file_redirections(t_cmd *cmd, int file_fd, int is_tty);
t_pipeinfo		setup_pipeline(int *prev_fd, int pipefd[2]);

int				get_in_readline_state(void);
void			set_in_readline_state(int state);
void			install_sigint_wait_handler(struct sigaction *old);
void			restore_signal_handler(struct sigaction *old_sa);
void			set_continuation_signal_handler(struct sigaction *old_sa);
void			signal_handler(int sig);
void			signal_ctlc_heredoc(int sig);
void			signal_ctlc_continuation(int sig);

void			env_command(t_cmd *cmd);
void			pwd_command(void);
void			exit_command(t_cmd *cmd);
void			unset_command(t_cmd *cmd);
void			export_command(t_cmd *cmd);
void			echo_command(t_cmd *cmd);
void			cd_command(t_cmd *cmd);
void			ch_dir(t_list **env, char *cur_dir, char *path);
void			chenv(t_list **env, char *new_dir, char *cur_dir);
void			ch_oldpwd_case(t_list **env, char *cur_dir);
void			direct_execute(t_cmd *cmd);
bool			is_built_in(t_cmd *cmd);
bool			handler_var(t_list **env, char *word, int size);
void			add_new_var(t_list **env, char *word);
int				is_valid_identifier(const char *str);
bool			handler_var(t_list **env, char *word, int size);
void			add_new_var(t_list **env, char *word);
void			order_env(t_list *env);

char			*find_command_in_path(char *command, t_list *env);
char			*check_direct_path(char *command);
char			*search_in_path_env(char *command, char **paths);
char			*get_value(t_list *lst, char *str);
char			*create_double_operator_token(char operator);
char			*create_single_operator_token(char operator);

char			*get_var_name_with_eq(char *raw_token, int start, int end);
char			*handle_special_vars(char *raw_token, int *pos);
char			*var_value(char *raw_token, int start, int end, t_list *env);

char			*get_display_path(char *pwd, char *home);
char			*join_with_color(char *color, char *text, char *reset);
char			*build_prompt_parts(char *user_colored, char *path_colored);
char			*get_current_pwd(t_list *env);
char			*create_prompt(t_list *env);

void			free_mem(char **str);
void			free_env(t_list **env);
void			free_cmd_start(t_cmd **cmd);
void			destroy_fsm(t_fsm **fsm);

int				count_args_in_range(t_token *start, t_token *end);
void			fill_args_in_range(t_cmd *cmd, t_token *start, t_token *end);
int				count_heredocs_in_range(t_token *start, t_token *end);
void			fill_heredocs(t_cmd *cmd, t_token *start, t_token *end);
void			assign_args_heredocs_loop(t_cmd *head, t_token *token_list);

#endif
