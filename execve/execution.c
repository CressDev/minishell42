/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:54:50 by cress             #+#    #+#             */
/*   Updated: 2026/01/12 20:45:14 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	direct_execute(t_cmd *cmd)
{
	char	*full_path;

	if (!cmd->args[0] || cmd->args[0][0])
		return (write(STDERR_FILENO, " : command not found\n", 22),
			exit(127), (void)0);
	full_path = find_command_in_path(cmd->args[0], cmd->envs->env);
	if (!full_path)
	{
		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
		write(STDERR_FILENO, ": command nor found\n", 20);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(full_path, cmd->args, cmd->envs->env);
	perror("execve failed");
	exit(126);
}
