/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:54:50 by cress             #+#    #+#             */
/*   Updated: 2026/01/13 21:20:31 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(full_path, cmd->args, cmd->envs->environ);
	perror("execve");
	exit(126);
}
