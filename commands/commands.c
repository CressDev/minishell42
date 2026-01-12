/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:31:48 by cress             #+#    #+#             */
/*   Updated: 2026/01/12 19:01:37 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return false;
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env_command(cmd->envs, cmd->args), true);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd_command(), true);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_command(cmd->envs, cmd->args), true);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (exit_command(cmd->args), true);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export_command(cmd->envs, cmd), true);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo_command(cmd), true);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd_command(cmd->envs, cmd), true);
	return (false);
}

void	commands_parse_execution(t_token **tokens, t_envs *envs, int is_tty)
{
	t_cmd	*cmd;
	t_cmd	*current;

	cmd = parse_tokens((*tokens), envs);
	current = cmd;
	while (current)
	{
		if (current->next)
		{
			execute_pipeline(cmd, is_tty);
			free_pipeline(cmd);
		}
		else if (current->input_file || current->output_file
			|| current->is_heredoc)
		{
			execute_redir(cmd, envs, is_tty);
			free_redirect(cmd);
		}
		else if (!is_built_in(current))
			direct_execute(envs->env, current->args, envs->environ);
		current = current->next;
	}
}
