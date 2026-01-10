/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:54:50 by cress             #+#    #+#             */
/*   Updated: 2026/01/10 17:24:54 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	direct_execute(t_list **env, char **args, char **environ)
{
	char	*full_path;

	if (!args[0] || args[0][0] == '\0')
		return (write(STDERR_FILENO, " : command not found\n", 22),
			exit(127), (void)0);
	full_path = find_command_in_path(args[0], *env);
	if (!full_path)
	{
		write(STDERR_FILENO, args[0], ft_strlen(args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(full_path, args, environ);
	perror("execve failed");
	exit(126);
}
