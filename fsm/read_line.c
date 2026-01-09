/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:27:13 by cress             #+#    #+#             */
/*   Updated: 2026/01/09 22:10:59 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_list *env)
{
	char	*pwd;
	char	*display_path;
	char	*user_colored;
	char	*path_colored;
	char	*user_name;

	pwd = get_current_pwd(env);
	if (!pwd)
		return (NULL);
	display_path = get_display_path(pwd, get_value(env, "HOME="));
	if (!display_path)
		return (free(pwd), write(1, "Malloc Error\n", 14), NULL);
	user_name = get_value(env, "USER=");
	if (!user_name)
		user_name = "Amonteag";
	user_colored = join_with_color(COLOR_GREEN, user_name, COLOR_RESET);
	path_colored = join_with_color(COLOR_BLUE, display_path, COLOR_RESET);
	if (!user_colored || !path_colored)
		return (free(pwd), free(display_path), free(user_colored),
			free(path_colored), write(1, "Malloc Error\n", 14), NULL);
	user_name = build_prompt_parts(user_colored, path_colored);
	return (free(pwd), free(display_path), free(user_colored),
		free(path_colored), user_name);
}

int	process_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[0] == '\0' || i == ft_strlen(line))
	{
		g_signal = 0;
		free(line);
		return (1);
	}
	return (0);
}

char	*create_line(t_list *env)
{
	char	*line;
	char	*prompt;
	int		is_tty;

	is_tty = isatty(STDIN_FILENO);
	set_in_readline_state(1);
	if (is_tty)
	{
		signal(SIGINT, &signal_handler);
		prompt = create_prompt(env);
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
	set_in_readline_state(0);
	return (line);
}

void	change_signal(void)
{
	int		is_tty;

	is_tty = isatty(STDIN_FILENO);
	if (is_tty && g_signal == 130)
		exit(130);
	if (is_tty)
		exit(g_signal);
}

void	read_line(t_envs *envs)
{
	char	*line;
	t_token	*tokens;
	int		is_tty;

	is_tty = isatty(STDIN_FILENO);
	while (1)
	{
		tokens = NULL;
		line = create_line((*envs->env));
		if (!line)
		{
			if (is_tty)
				change_signal();
			else
				break ;
		}
		if (process_empty_line(line))
			continue ;
		add_history(line);
		entry_point(line, &tokens);
		if (tokens)
			execute_and_cleanup(tokens, is_tty);
		free(line);
	}
}
