/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:03:47 by cress             #+#    #+#             */
/*   Updated: 2025/12/23 20:29:42 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_oldpwd_case(t_list **env, char *cur_dir)
{
	char	*oldpwd;
	char	*oldpwd_copy;

	oldpwd = get_value(*env, "OLDPWD=");
	if (!oldpwd)
		return (write(1, "cd: OLDPWD not set\n", 19), g_signal = 1,
			(void)0);
	oldpwd_copy = ft_strdup(oldpwd);
	if (!oldpwd_copy)
		return (g_signal = 1, (void)0);
	ch_dir(env, cur_dir, oldpwd);
	if (g_signal == 0)
		ft_printf("%s\n", oldpwd_copy);
	free(oldpwd_copy);
}

bool	is_delete_env(t_list **env, t_list *cur, char *tokens, t_list *prev)
{
	int	size;

	size = ft_strlen(tokens);
	if (ft_strncmp(cur->content, tokens, size) == 0)
	{
		if (prev == NULL)
			*env = cur->next;
		else
			prev->next = cur->next;
		ft_lstdelone(cur, free);
		return (true);
	}
	return (false);
}

void	unset_command(t_list **env, char **tokens)
{
	t_list	*cur;
	t_list	*prev;
	int		i;

	if (ft_count(tokens) == 1)
		return (g_signal = 0, (void)0);
	i = 1;
	while (i < ft_count(tokens))
	{
		cur = *env;
		prev = NULL;
		while (cur)
		{
			if (is_delete_env(env, cur, tokens[i], prev))
				break ;
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	g_signal = 0;
}

void	env_command(t_list *env, char **tokens)
{
	t_list	*cur;

	if (ft_count(tokens) > 1)
		return (ft_printf("env: %s: The file or directory does not exit"),
			g_signal = 127, (void)0);
	cur = env;
	while (cur)
	{
		if (cur->content)
			ft_printf("%s\n", cur->content);
		cur = cur->next;
	}
	g_signal = 0;
}

void	pwd_command(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (write(1, "Error, no pwd\n", 14), g_signal = 1, (void)0);
	ft_printf("%s\n", pwd);
	free(pwd);
	g_signal = 0;
}
