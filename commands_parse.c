/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 10:01:19 by cress             #+#    #+#             */
/*   Updated: 2025/12/30 09:50:44 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_pipe_syntax(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens || !tokens[0])
		return (true);
	if (ft_strcmp(tokens[0], "|") == 0)
		return (write(2, "syntax error\n", 14), g_signal = 2, false);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (tokens[i + 1] && ft_strcmp(tokens[i + 1], "|") == 0)
				return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
		}
		i++;
	}
	return (true);
}

bool	line_ends_with_pipe(char *line)
{
	int	len;
	int	i;

	if (!line || !*line)
		return (false);
	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && is_whitespace(line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
	{
		write(2, "syntax error\n", 14);
		g_signal = 2;
		return (free(line), true);
	}
	return (false);
}

bool	has_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') != 0)
			return (true);
		i++;
	}
	return (false);
}

bool	has_redirections(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0
			|| ft_strcmp(tokens[i], "<<") == 0)
			return (true);
		i++;
	}
	return (false);
}
