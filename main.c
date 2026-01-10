/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:24:05 by cress             #+#    #+#             */
/*   Updated: 2025/08/20 10:24:33 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	show_init_ms(void)
{
	ft_printf("\033[95m%s\033[0m", "\n\
		███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
		████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
		██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
		██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
		██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
		\n	\n");
}

/**
 * @brief Reads input from the user or standard input.
 *
 * This function generates a custom prompt for the minishell when running
 * in interactive mode and reads user input using readline.
 * If the shell is running in non-interactive mode, it reads directly from
 * standard input using get_next_line.
 *
 * In non-interactive mode, the trailing newline character is removed
 * to ensure consistent input formatting.
 *
 * @param envs Pointer to the environment list used to build the prompt.
 * @param is_tty Non-zero value if the shell is running in interactive mode.
 *
 * @return A pointer to the read input string, or NULL on failure or EOF.
 */
static char	*read_input(t_list *envs, int is_tty)
{
	char	*line;
	char	*prompt;

	if (is_tty)
	{
		prompt = create_prompt(envs);
		if (!prompt)
			return (NULL);
		line = readline(prompt);
		free(prompt);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

static t_list	**init_env(char **environ)
{
	t_list	**env;
	t_list	*new;
	int		i;

	env = malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	*env = NULL;
	i = 0;
	if (!environ || !environ[0])
	{
		*env = ft_lstnew(ft_strdup("SHLVL=1"));
		return (env);
	}
	*env = ft_lstnew(ft_strdup(environ[0]));
	if (!*env)
		return (free(env), NULL);
	while (environ[++i])
	{
		new = ft_lstnew(ft_strdup(environ[i]));
		if (!new)
			return (ft_lstclear(env, free), free(env), NULL);
		ft_lstadd_back(env, new);
	}
	return (env);
}

/**
 * @brief Main loop of the shell.
 *
 * This function controls the core execution flow of the minishell.
 * It continuously reads user input, handles end-of-file (EOF) conditions,
 * signal interruptions, and tokenizes the input using a Finite State Machine (FSM).
 * Once tokenized, the input is parsed and executed as shell commands.
 *
 * The loop runs indefinitely until an EOF condition is detected or an
 * explicit exit is triggered.
 *
 * @param envs Pointer to the environment structure containing both the inherited
 * environment from the parent shell and the minishell's own environment.
 */
static void	shell_main_loop(t_envs *envs)
{
	char	*line; /**< Stores the user input string. */
	int		is_tty;
	t_token	*tokens; /**< Linked list of tokenized commands. */

	is_tty = isatty(STDIN_FILENO);
	while (1)
	{
		g_signal = 0;
		tokens = NULL;
		line = read_input(envs, is_tty);
		if (handle_eof(line, is_tty))
			break ;
		if (handle_interrupt(line))
			continue ;
		if (!obtain_tokens(line, &tokens))
			continue ;
		add_history(line);
		commands_parse_execution(&tokens, envs, is_tty);
		free_tokens(&tokens);
	}
}

int	main(int ac, char **av, char **environ)
{
	t_list	**env;
	t_envs	*envs;

	(void)av;
	if (ac > 1)
		return (1);
	if (isatty(STDIN_FILENO))
		show_init_ms();
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(environ);
	if (env == NULL)
		return (write(1, "Error\n", 6));
	shell_main_loop(envs);
	ft_lstclear(&env, free);
}
