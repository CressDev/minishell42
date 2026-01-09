/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:31:48 by cress             #+#    #+#             */
/*   Updated: 2026/01/09 22:17:57 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(char **args, t_envs *envs)
{
	if (!args || !args[0])
		return false;

	if (ft_strcmp(args[0], "env") == 0)
		return (env_command(*envs->env, args), true);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_command(), true);
	if (ft_strcmp(args[0], "unset") == 0)
		return (unset_command(envs, args), true);
	if (ft_strcmp(args[0], "exit") == 0)
		return (exit_command(args), true);
	if (ft_strcmp(args[0], "export") == 0)
		return (export_command(envs, args), true);
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_command(args), true);
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd_command(envs, args), true);
	return (false);
}

static void	exec_redirection_cmd(t_cmd *cmd, t_envs *envs, int is_tty)
{
	exec_redir(cmd, envs, is_tty);
	free_redirect(cmd);
}

static void	exec_pipeline_cmd(t_cmd *cmd, int is_tty)
{
	execute_pipeline(cmd, is_tty);
	free_pipeline(cmd);
}

void	exec_command(t_cmd *cmd, t_envs *envs, int is_tty)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->next)
			exec_pipeline_cmd(current, is_tty);
		else if (current->input_file || current->output_file || current->is_heredoc)
			exec_redirection_cmd(current, envs, is_tty);
		else if (!is_built_in(current->args, envs->env))
			direct_execute(envs->env, current->args, envs->environ);
		current = current->next;
	}
}
