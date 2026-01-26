/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:00:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/26 21:44:12 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int saved_stdin, int saved_stdout, int input_fd,
				int output_fd)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
}

int	setup_input_redirect(t_cmd *cmd)
{
	int	input_fd;

	if (!cmd->input_file)
		return (-1);
	input_fd = open(cmd->input_file, O_RDONLY);
	if (input_fd == -1)
	{
		perror(cmd->input_file);
		g_signal = 1;
		return (-1);
	}
	return (input_fd);
}

int	setup_output_redirect(t_cmd *cmd)
{
	int	output_fd;

	if (!cmd->output_file)
		return (-1);
	if (cmd->append)
		output_fd = open(cmd->output_file, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else
		output_fd = open(cmd->output_file, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	if (output_fd == -1)
	{
		perror(cmd->output_file);
		g_signal = 1;
		return (-1);
	}
	return (output_fd);
}

void	execute_redir(t_cmd *cmd, int is_tty)
{
	int	saved_stdin;
	int	saved_stdout;
	int	input_fd;
	int	output_fd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->is_heredoc)
		input_fd = setup_all_heredocs(cmd, is_tty);
	else
		input_fd = setup_input_redirect(cmd);
	output_fd = setup_output_redirect(cmd);
	if (input_fd == -1 && cmd->is_heredoc)
		return (restore_fds(saved_stdin, saved_stdout, -1, output_fd));
	if (input_fd == -1 && cmd->input_file)
		return (restore_fds(saved_stdin, saved_stdout, -1, output_fd));
	if (output_fd == -1 && cmd->output_file)
		return (restore_fds(saved_stdin, saved_stdout, input_fd, -1));
	if (input_fd != -1)
		dup2(input_fd, STDIN_FILENO);
	if (output_fd != -1)
		dup2(output_fd, STDOUT_FILENO);
	if (!is_built_in(cmd))
		direct_execute(cmd);
	restore_fds(saved_stdin, saved_stdout, input_fd, output_fd);
}
