/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 09:34:50 by cress             #+#    #+#             */
/*   Updated: 2026/01/16 20:17:14 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc_input(int is_tty)
{
	char	*line;

	if (is_tty)
		line = readline("> ");
	else
		line = get_next_line(STDIN_FILENO);
	if (!is_tty && line && ft_strlen(line) > 0
		&& line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int	process_heredoc_line(char *line, char *delimiter, int pipefd[2])
{
	if (g_signal == 130 || !line)
	{
		if (line)
			free(line);
		return (-1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
	return (0);
}

int	read_heredoc_lines(char *delimiter, int pipefd[2], int is_tty)
{
	char	*line;
	int		result;

	while (1)
	{
		line = read_heredoc_input(is_tty);
		result = process_heredoc_line(line, delimiter, pipefd);
		if (result == -1)
			return (-1);
		if (result == 1)
			return (0);
	}
}

int	setup_heredoc(char *delimiter, int is_tty)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	signal(SIGINT, signal_ctlc_heredoc);
	g_signal = 0;
	if (read_heredoc_lines(delimiter, pipefd, is_tty) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		signal(SIGINT, signal_handler);
		return (-1);
	}
	close(pipefd[1]);
	signal(SIGINT, signal_handler);
	return (pipefd[0]);
}

int	setup_all_heredocs(t_cmd *cmd, int is_tty)
{
	int	fd;
	int	last_fd;
	int	i;

	i = 0;
	last_fd = -1;
	while (cmd->heredoc_delimiter && cmd->heredoc_delimiter[i])
	{
		fd = setup_heredoc(cmd->heredoc_delimiter[i], is_tty);
		if (fd == -1)
		{
			if (last_fd != -1)
				close(last_fd);
			return (-1);
		}
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		i++;
	}
	return (last_fd);
}
