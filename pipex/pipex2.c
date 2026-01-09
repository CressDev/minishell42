/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:15:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/09 22:20:12 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_pipe_child(t_cmd *current, int *prev_fd, int pipefd[2],
						int *out_fd)
{
	if (current->next)
		*out_fd = pipefd[1];
	else
		*out_fd = -1;
	if (*prev_fd != -1)
		dup2(*prev_fd, STDIN_FILENO);
	if (*out_fd != -1)
		dup2(*out_fd, STDOUT_FILENO);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

t_pipeinfo	setup_pipeline(int *prev_fd, int pipefd[2])
{
	t_pipeinfo	pipes;

	pipes.prev_fd = prev_fd;
	pipes.pipefd[0] = pipefd[0];
	pipes.pipefd[1] = pipefd[1];
	return (pipes);
}

void	setup_file_redirections(t_cmd *cmd, int file_fd, int is_tty)
{
	if (cmd->is_heredoc || cmd->input_file)
	{
		if (cmd->is_heredoc)
			file_fd = setup_heredoc(cmd->heredoc_delimiter, is_tty);
		else
			file_fd = setup_input_redirect(cmd);
		if (file_fd != -1)
		{
			dup2(file_fd, STDIN_FILENO);
			close(file_fd);
		}
		else
			exit(1);
	}
	if (cmd->output_file)
	{
		file_fd = setup_output_redirect(cmd);
		if (file_fd != -1)
		{
			dup2(file_fd, STDOUT_FILENO);
			close(file_fd);
		}
		else
			exit(1);
	}
}

void	setup_pipe_redirections(int input_fd, int output_fd)
{
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != -1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	execute_pipeline_child(t_cmd *cmd, int input_fd, int output_fd,
							t_exec_data *exec_data)
{
	int	file_fd;

	file_fd = -1;
	setup_pipe_redirections(input_fd, output_fd);
	setup_file_redirections(cmd, file_fd, exec_data->is_tty);
	if (is_built_in(exec_data->envs->env, cmd->args))
		exit(g_signal);
	else
		direct_execute(exec_data->envs->env, cmd->args, exec_data->envs->environ);
}
