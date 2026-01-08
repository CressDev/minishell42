/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:10:15 by amonteag          #+#    #+#             */
/*   Updated: 2026/01/08 21:55:07 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**init_env(char **environ)
{
	t_list	**env;
	t_list	*new;
	int		i;

	env = malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	*env = NULL;
	i = 0;
	if (!environ || !environ[0])
	{
		*env = ft_lstnew(ft_strdup("SHLVL=1"));
		return (env);
	}
	*env = ft_lstnew(ft_strdup(environ[0]));
	if (!*env)
		return (free(env), NULL);
	while (environ[++i])
	{
		new = ft_lstnew(ft_strdup(environ[i]));
		if (!new)
			return (ft_lstclear(env, free), free(env), NULL);
		ft_lstadd_back(env, new);
	}
	return (env);
}

void	execute_and_cleanup(t_cmd *cmd, char *line, int is_tty)
{
	exec_command(cmd, line, is_tty);
	if (is_tty)
		add_history(line);
	free(line);
}

t_cmd	*init_cmd(char **environ, t_list **env)
{
	t_cmd	*cmd;
	t_list	**env;

	cmd = malloc(sizeof(t_cmd));
	if (cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->env = env;
	cmd->environ = environ;
	cmd->next = NULL;
	return (cmd);
}
