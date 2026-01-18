/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:54:50 by cress             #+#    #+#             */
/*   Updated: 2026/01/16 18:48:55 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void create_children(char *full_path, char **args, char **envirom)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, envirom);
		perror("execve failed");
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
	}
	else
	{
		perror("fork failed");
		g_signal = 1;
	}
}

void	direct_execute(t_cmd *cmd)
{
	char	*full_path;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		write(STDERR_FILENO, ": command not found", 20);
		exit(127);
	}
	full_path = find_command_in_path(cmd->args[0], *cmd->envs->env);
	if (!full_path)
	{
		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		g_signal = 127;
		return ;
	}
	create_children(full_path, cmd->args, cmd->envs->environ);
	free(full_path);
}
