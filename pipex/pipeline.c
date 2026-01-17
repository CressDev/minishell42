/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:52:04 by cress             #+#    #+#             */
/*   Updated: 2026/01/17 19:35:28 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_pipeline_completion(t_exec_data *exec_data)
{
	int					status;
	pid_t				pid;
	struct sigaction	sa_old;

	install_sigint_wait_handler(&sa_old);
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == exec_data->last_child_pid)
		{
			if (WIFEXITED(status))
				g_signal = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_signal = 128 + WTERMSIG(status);
		}
		pid = waitpid(-1, &status, 0);
	}
	restore_signal_handler(&sa_old);
}

static void	handle_parent_process(pid_t pid, t_pipeinfo *pipes, t_cmd *current,
								t_exec_data *exec_data)
{
	exec_data->last_child_pid = pid;
	if (*(pipes->prev_fd) != -1)
		close(*(pipes->prev_fd));
	if (current->next)
	{
		close(pipes->pipefd[1]);
		*(pipes->prev_fd) = pipes->pipefd[0];
	}
}

int	execute_single_pipe_cmd(t_cmd *current, int *prev_fd, int pipefd[2],
							t_exec_data *exec_data)
{
	pid_t		pid;
	t_pipeinfo	pipes;
	int			out_fd;

	if (current->next && pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		close_unused_pipe_child(current, prev_fd, pipefd, &out_fd);
		execute_pipeline_child(current, *prev_fd, out_fd, exec_data);
		exit(g_signal);
	}
	else if (pid > 0)
	{
		pipes = setup_pipeline(prev_fd, pipefd);
		handle_parent_process(pid, &pipes, current, exec_data);
	}
	else
		return (perror("fork"), -1);
	return (0);
}

void	execute_pipeline(t_cmd *cmd, int is_tty)
{
	t_cmd		*current;
	int			pipefd[2];
	int			prev_fd;
	t_exec_data	exec_data;

	exec_data.is_tty = is_tty;
	exec_data.last_child_pid = -1;
	prev_fd = -1;
	current = cmd;
	while (current)
	{
		if (execute_single_pipe_cmd(current, &prev_fd, pipefd,
				&exec_data) == -1)
			return ;
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_pipeline_completion(&exec_data);
}
