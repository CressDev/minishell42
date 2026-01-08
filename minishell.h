/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:25:30 by cress             #+#    #+#             */
/*   Updated: 2026/01/08 18:51:56 by kjroydev         ###   ########.fr       */
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
	size_t			counter; /**< Aux counter of the FSM. */
	size_t			token_capacity; /**< Int to represet initial buffer size */
	bool			has_error; /**< Boolean to control error state. */
	char			*input; /**< User input (readline). */
	char			*token; /**< Buffer to construct tokens. */
}	t_fsm;

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
	int				type; /**< Type of the content (determined by enum). */
	int				quote; /**< Quote type. */
	struct s_token	*next; /**< Next token. */
}	t_token;

void	entry_point(char *input, t_token **tokens);
t_fsm	*init_fsm(char *input);
typedef bool	(*t_state_handler)(t_fsm *, char, t_token **);
bool	state_start(t_fsm *fsm, char c, t_token **tokens);
bool	state_word(t_fsm *fsm, char c, t_token **tokens);
bool	state_squote(t_fsm *fsm, char c, t_token **tokens);
bool	state_dquote(t_fsm *fsm, char c, t_token **tokens);
bool	state_pipe(t_fsm *fsm, char c, t_token **tokens);
bool	state_end(t_fsm *fsm, char c, t_token **tokens);
bool	state_redirect(t_fsm *fsm, char c, t_token **tokens);
bool	state_error(t_fsm *fsm, char c, t_token **tokens);
void	error_handler(t_fsm *fsm, const char *line);
void	default_state(t_fsm *fsm);
void	create_token(t_fsm *fsm, t_token **tokens, int quoted);
void	destroy_fsm(t_fsm **fsm);

t_token	*init_token(t_fsm *fsm, int quoted);
void	token_append_str(t_fsm *fsm, const char *str, t_token **tokens);
void	token_append_char(t_fsm *fsm, const char c, t_token **tokens);
void	expand_token_buffer(t_fsm *fsm, t_token **tokens);
void	token_add_back(t_token **tokens, t_token *new);
void	free_tokens(t_token **tokens);

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	char			*heredoc_delimiter;
	int				append;
	int				is_heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec_data
{
	t_list	**env;
	char	**environ;
	int		is_tty;
	pid_t	last_child_pid;
}	t_exec_data;

typedef struct s_pipeinfo
{
	int	*prev_fd;
	int	pipefd[2];
}	t_pipeinfo;

void		process_output_redirect(t_cmd *cmd, char **tokens, int i);
void		fill_args_array(t_cmd *cmd, char **tokens);
void		free_redirect(t_cmd *cmd);
void		restore_fds(int saved_stdin, int saved_stdout, int input_fd,
				int output_fd);
void		exec_redir(t_cmd *cmd, t_list **env, char **environ, int is_tty);
int			count_args_no_redirect(char **tokens);
int			process_redirections(t_cmd *cmd, char **tokens);
int			process_input_redirect(t_cmd *cmd, char **tokens, int i);
int			setup_input_redirect(t_cmd *cmd);
int			setup_output_redirect(t_cmd *cmd);
int			setup_heredoc(char *delimiter, int is_tty);
t_cmd		*parse_redirections(char **tokens);
bool		has_redirections(char **tokens);

void		close_unused_pipe_child(t_cmd *current, int *prev_fd, int pipefd[2],
				int *out_fd);
void		list_pipeline(t_cmd **first_cmd, t_cmd *new_cmd);
void		execute_pipeline(t_cmd *cmd_list, t_list **env, char **environ,
				int is_tty);
void		execute_pipeline_child(t_cmd *cmd, int input_fd, int output_fd,
				t_exec_data *exec_data);
void		setup_pipe_redirections(int input_fd, int output_fd);
void		setup_file_redirections(t_cmd *cmd, int file_fd, int is_tty);
void		free_pipeline(t_cmd *cmd_list);
int			execute_single_pipe_cmd(t_cmd *current, int *prev_fd, int pipefd[2],
				t_exec_data *exec_data);
bool		validate_pipe_syntax(char **tokens);
bool		line_ends_with_pipe(char *line);
bool		has_pipes(char **tokens);
t_cmd		*parse_pipeline(char **tokens);
char		**create_cmd_tokens(char **tokens, int start, int end);
t_cmd		*add_cmd_to_pipeline(char **tokens, int start, int end);
t_pipeinfo	setup_pipeline(int *prev_fd, int pipefd[2]);

int			get_in_readline_state(void);
void		set_in_readline_state(int state);
void		install_sigint_wait_handler(struct sigaction *old);
void		set_continuation_state(int state);
void		restore_signal_handler(struct sigaction *old_sa);
void		set_continuation_signal_handler(struct sigaction *old_sa);
void		signal_handler(int sig);
void		signal_ctlc_heredoc(int sig);
void		signal_ctlc_continuation(int sig);
int			get_continuation_state(void);
void		read_line(t_list *env, char **environ);
void		free_mem(char **str);
void		execute_and_cleanup(t_list **env, char *line, char **environ,
				int is_tty);
int			is_closed_line(char *line);
int			process_empty_line(char *line);
char		*process_single_continuation(char *line);
char		*handle_continuation(char *line);
char		*get_separator(char *line, char *continuation);
char		*create_line(t_list *env);

void		show_tokens(char **tokens, char *token, int i);
void		exec_command(t_list **env, char *line, char **environ, int is_tty);
void		env_command(t_list *env, char **tokens);
void		pwd_command(void);
void		exit_command(char **tokens);
void		unset_command(t_list **env, char **tokens);
void		export_command(t_list **env, char **words);
void		add_new_var(t_list **env, char *word);
void		echo_command(char **tokens);
void		cd_command(t_list **env, char **tokens);
void		ch_dir(t_list **env, char *cur_dir, char *path);
void		chenv(t_list **env, char *new_dir, char *cur_dir);
void		ch_oldpwd_case(t_list **env, char *cur_dir);
void		is_execute(t_list **env, char **tokens, char **environ);
void		direct_execute(t_list **env, char **tokens, char **environ);
bool		is_built_in(t_list **env, char **tokens);
bool		handler_var(t_list **env, char *word, int size);

int			is_operator(char c);
int			is_whitespace(char c);
int			skip_spaces(char *line, int pos);
int			skip_word_token(char *line, int pos);
int			count_tokens(char *line, int i);
char		*extract_operator_token_and_advance(char *line, int *pos);
char		*extract_operator_token(char *line, int pos);
char		*extract_token(char *line, int *pos, t_list *env);
char		**tokenize_shell_line(char *line, t_list *env);
char		*find_command_in_path(char *command, t_list *env);
char		*check_direct_path(char *command);
char		*search_in_path_env(char *command, char **paths);
char		*get_value(t_list *lst, char *str);
char		*create_double_operator_token(char operator);
char		*create_single_operator_token(char operator);
char		*extract_left_operator_token(char *line, int pos);
char		*extract_right_operator_token(char *line, int pos);
char		*extract_operator_token(char *line, int pos);

int			calculate_unquoted_len(char *str, int start, int end);
char		*process_quotes(char *str, int start, int end);
char		*process_expansions(char *str, t_list *env);
char		*expand_variable(char *str, int *pos, t_list *env);
char		*handle_special_vars(char *str, int *pos);
char		*extract_var_value(char *str, int start, int end, t_list *env);
char		*get_var_name_with_eq(char *str, int start, int end);
char		*append_expansion(char *result, char *expanded);
char		*process_char_expan(char *result, char *str, int *i, t_list *env);

char		*get_display_path(char *pwd, char *home);
char		*join_with_color(char *color, char *text, char *reset);
char		*build_prompt_parts(char *user_colored, char *path_colored);
char		*get_current_pwd(t_list *env);
char		*create_prompt(t_list *env);

#endif
