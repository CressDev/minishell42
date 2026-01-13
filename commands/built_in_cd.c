/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:06:15 by cress             #+#    #+#             */
/*   Updated: 2026/01/13 21:04:27 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chenv(t_list **env, char *new_dir, char *cur_dir)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strjoin("OLDPWD=", cur_dir);
	if (!old_pwd)
		return (g_signal = 1, (void)0);
	new_pwd = ft_strjoin("PWD=", new_dir);
	if (!new_pwd)
		return (free(old_pwd), g_signal = 1, (void)0);
	if (!handler_var(env, old_pwd, 0))
		add_new_var(env, old_pwd);
	if (!handler_var(env, new_pwd, 0))
		add_new_var(env, new_pwd);
	free(old_pwd);
	free(new_pwd);
	g_signal = 0;
}

void	ch_dir(t_list **env, char *cur_dir, char *path)
{
	char	*new_pwd;
	char	*ret;

	if ((access(path, F_OK) == -1) || (chdir(path) == -1))
	{
		ret = ft_strjoin("cd: ", path);
		if (!ret)
			return (g_signal = 1, (void)0);
		g_signal = 1;
		return (perror(ret), free(ret));
	}
	if (path[0] != '/')
	{
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
			return (perror("pwd"), g_signal = 1, (void)0);
		chenv(env, new_pwd, cur_dir);
		return (free(new_pwd), (void)0);
	}
	chenv(env, path, cur_dir);
}

void	ch_cases(t_list **env, char *cur_dir, int cases)
{
	char	*new_dir;

	if (!cases)
	{
		new_dir = get_value(*env, "HOME=");
		if (!new_dir)
			return (write(1, "cd: undefined HOME\n", 20),
				g_signal = 1, (void)0);
		ch_dir(env, cur_dir, new_dir);
	}
	else
		ch_oldpwd_case(env, cur_dir);
}

void	ch_parent(t_list **env, char *cur_dir)
{
	char	*new_dir;
	char	*last_slash;
	int		slash_pos;

	if (ft_strcmp(cur_dir, "/") == 0)
		return (g_signal = 0, (void)0);
	last_slash = ft_strrchr(cur_dir, '/');
	if (!last_slash)
		return (g_signal = 0, (void)0);
	slash_pos = last_slash - cur_dir;
	if (slash_pos == 0)
		new_dir = ft_strdup("/");
	else
		new_dir = ft_substr(cur_dir, 0, slash_pos);
	if (!new_dir)
		return (perror(""), g_signal = 1, (void)0);
	ch_dir(env, cur_dir, new_dir);
	free(new_dir);
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
		return (write(2, "cd: too many arguments\n", 24), free(cur_dir),
			g_signal = 1, (void)0);
	if (!cmd->args[1] || (cmd->args[1] && cmd->args[1][0] == '~'))
		return (ch_cases(cmd->envs->env, cur_dir, 0), free(cur_dir), (void)0);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		return (ch_parent(cmd->envs->env, cur_dir), free(cur_dir), (void)0);
	else if (cmd->args[1][0] == '-')
		return (ch_cases(cmd->envs->env, cur_dir, 1), free(cur_dir), (void)0);
	else
		return (ch_dir(cmd->envs->env, cur_dir, cmd->args[1]), free(cur_dir), (void)0);
}
