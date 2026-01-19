/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:42:50 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/19 08:48:46 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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
