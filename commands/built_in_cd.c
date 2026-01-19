/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:06:15 by cress             #+#    #+#             */
/*   Updated: 2026/01/19 11:35:40 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cd_case(t_cmd *cmd, char *cur_dir)
{
	if (!cmd->args[1] || cmd->args[1][0] == '~')
		ch_cases(cmd->envs->env, cur_dir, 0);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		ch_parent(cmd->envs->env, cur_dir);
	else if (cmd->args[1][0] == '-')
		ch_cases(cmd->envs->env, cur_dir, 1);
	else
		ch_dir(cmd->envs->env, cur_dir, cmd->args[1]);
}

void	cd_command(t_cmd *cmd)
{
	char	*cur_dir;
	char	*env_pwd;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
	{
		env_pwd = get_value(*cmd->envs->env, "PWD=");
		if (env_pwd)
			cur_dir = ft_strdup(env_pwd);
		else
			cur_dir = ft_strdup("/");
		if (!cur_dir)
			return (perror("malloc"), g_signal = 1, (void)0);
	}
	if (ft_count(cmd->args) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		free(cur_dir);
		g_signal = 1;
		return ;
	}
	exec_cd_case(cmd, cur_dir);
	free(cur_dir);
}
