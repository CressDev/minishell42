/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:19:30 by cress             #+#    #+#             */
/*   Updated: 2026/01/18 07:58:56 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_identifier(const char *str)
{
	int i = 0;
	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return 0;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return 1;
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
		if (ft_strncmp(current->content, word, size + 1) == 0)
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

	if (!ft_strchr(word, '='))
		return;
	new_content = ft_strdup(word);
	if (!new_content)
		return (perror("export"), g_signal = 1, (void)0);
	new_node = ft_lstnew(new_content);
	if (!new_node)
		return (perror("export"), free((new_content)), g_signal = 1, (void)0);
	ft_lstadd_back(env, new_node);
}

static void export_process_args(t_list **env, char **words)
{
	int		i;
	char	*eq;
	int		valid;
	size_t	len;
	char	tmp;

	i = 1;
	while (words[i])
	{
		eq = ft_strchr(words[i], '=');
		valid = 0;
		if (eq)
		{
			len = eq - words[i];
			tmp = words[i][len];
			words[i][len] = '\0';
			valid = is_valid_identifier(words[i]);
			words[i][len] = tmp;
		}
		else
			valid = is_valid_identifier(words[i]);
		if (!valid)
		{
			ft_printf("export: `%s': not a valid identifier\n", words[i]);
			g_signal = 1;
		}
		else if (!handler_var(env, words[i], 0))
			add_new_var(env, words[i]);
		i++;
	}
}

void	export_command(t_list **env, char **words)
{
	t_list	*current;

	if (ft_count(words) == 1)
	{
		current = *env;
		order_env(current);
		while (current)
		{
			ft_printf("declare -x %s\n", current->content);
			current = current->next;
		}
	}
	else
		export_process_args(env, words);
}

