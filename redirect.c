/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:00:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/08 22:12:20 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_redir(t_cmd *cmd, int is_tty)
{
	int	saved_stdin;
	int	saved_stdout;
	int	input_fd;
	int	output_fd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->is_heredoc)
		input_fd = setup_heredoc(cmd->heredoc_delimiter, is_tty);
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
	if (!is_built_in(cmd->env, cmd->args))
		is_execute(cmd->env, cmd->args, cmd->environ);
	restore_fds(saved_stdin, saved_stdout, input_fd, output_fd);
}
