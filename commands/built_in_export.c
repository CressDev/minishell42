 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:19:30 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 11:47:00 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handler_var(t_list **env, char *word, int size)
{
	t_list	*current;
	char	*new_content;
	char	*old_content;

	current = *env;
	new_content = ft_strdup(word);
	if (!new_content)
		return (perror("export"), g_signal = 1, false);
	while (new_content[size] && new_content[size] != '=')
		size++;
	while (current)
	{
		if (ft_strncmp((char *)current->content, word, size + 1) == 0)
		{
			old_content = current->content;
			current->content = new_content;
			free(old_content);
			return (true);
		}
		current = current->next;
	}
	return (free(new_content), false);
}

void	add_new_var(t_list **env, char *word)
{
	t_list	*new_node;
	char	*new_content;

	new_content = ft_strdup(word);
	if (!new_content)
		return (perror("export"), g_signal = 1, (void)0);
	new_node = ft_lstnew(new_content);
	if (!new_node)
		return (perror("export"), free((new_content)), g_signal = 1, (void)0);
	ft_lstadd_back(env, new_node);
}

void	order_env(t_list *env)
{
	t_list	*current;
	t_list	*cur;
	char	*aux;

	current = env;
	while (current && current->next != NULL)
	{
		cur = env;
		while (cur && cur->next != NULL)
		{
			if (ft_strcmp(cur->content, cur->next->content) > 0)
			{
				aux = cur->content;
				cur->content = cur->next->content;
				cur->next->content = aux;
			}
			cur = cur->next;
		}
		current = current->next;
	}
}

void	export_command(t_cmd *cmd)
{
	t_list	*current;
	int		i;

	if (cmd->argc == 1)
	{
		current = *cmd->envs->env;
		order_env(current);
		while(current)
		{
			ft_printf("declare -x %s\n", current->content);
			current = current->next;
		}
	}
	else
	{
		i = 1;
		while (i < cmd->argc)
		{
			if (!handler_var(cmd->envs->env, cmd->args[i], 0))
				add_new_var(cmd->envs->env, cmd->args[i]);
			i++;
		}
	}
	g_signal = 0;
}
