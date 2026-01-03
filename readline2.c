/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:10:15 by amonteag          #+#    #+#             */
/*   Updated: 2026/01/03 08:59:11 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_separator(char *line, char *continuation)
{
	if (!is_closed_line(line))
	{
		if (continuation && continuation[0] != '\0'
			&& ft_strcmp(continuation, "\"") != 0)
			return ("\n");
		else
			return ("");
	}
	else
		return (" ");
}

char	*process_single_continuation(char *line)
{
	char				*continuation;
	char				*temp;
	char				*full_line;
	struct sigaction	old_sa;

	g_signal = 0;
	set_continuation_signal_handler(&old_sa);
	write(1, "> ", 2);
	continuation = get_next_line(STDIN_FILENO);
	restore_signal_handler(&old_sa);
	if (!continuation || g_signal == 130)
	{
		if (continuation)
			free(continuation);
		return (g_signal = 0, NULL);
	}
	if (continuation && ft_strlen(continuation) > 0
		&& continuation[ft_strlen(continuation) - 1] == '\n')
		continuation[ft_strlen(continuation) - 1] = '\0';
	temp = ft_strjoin(line, get_separator(line, continuation));
	full_line = ft_strjoin(temp, continuation);
	return (free(temp), free(continuation), full_line);
}

char	*handle_continuation(char *line)
{
	char	*result;
	char	*new_line;

	result = line;
	while (!is_closed_line(result) || line_ends_with_pipe(result))
	{
		new_line = process_single_continuation(result);
		if (!new_line)
		{
			free(result);
			g_signal = 0;
			return (NULL);
		}
		free(result);
		result = new_line;
		if (!result)
			break ;
	}
	return (result);
}

int	process_empty_line(char *line)
{
	size_t	i;

	i = skip_spaces(line, 0);
	if (line[0] == '\0' || i == ft_strlen(line))
	{
		g_signal = 0;
		free(line);
		return (1);
	}
	return (0);
}

void	execute_and_cleanup(t_list **env, char *line, char **environ,
						int is_tty)
{
	exec_command(env, line, environ, is_tty);
	if (is_tty && !is_whitespace(line[0]))
		add_history(line);
	free(line);
}
