/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:10:15 by amonteag          #+#    #+#             */
/*   Updated: 2026/01/22 21:35:57 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name_with_eq(char *raw_token, int start, int end)
{
	char	*var_name;
	char	*var_name_eq;

	var_name = ft_substr(raw_token, start, end - start);
	if (!var_name)
		return (NULL);
	var_name_eq = ft_strjoin(var_name, "=");
	free(var_name);
	if (!var_name_eq)
		return (NULL);
	return (var_name_eq);
}

char	*handle_special_vars(char *raw_token, int *pos)
{
	char	*result;

	if (raw_token[*pos + 1] == '?')
	{
		*pos = *pos + 2;
		result = ft_itoa(g_signal);
		if (!result)
		{
			write(2, "Error: malloc failed for exit code\n", 36);
			return (NULL);
		}
		return (result);
	}
	if (raw_token[*pos + 1] == '-')
	{
		*pos = *pos + 2;
		result = ft_strdup("himBHs");
		if (!result)
			return (write(2, "Error: malloc failed for shell flags\n", 38),
				NULL);
		return (result);
	}
	return (NULL);
}

char	*var_value(char *raw_token, int start, int end, t_list *env)
{
	char	*var_name_eq;
	char	*var_value;
	char	*result;

	var_name_eq = get_var_name_with_eq(raw_token, start, end);
	if (!var_name_eq)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty string\n", 39);
		return (result);
	}
	var_value = get_value(env, var_name_eq);
	free(var_name_eq);
	if (!var_value)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty var\n", 36);
		return (result);
	}
	result = ft_strdup(var_value);
	if (!result)
		write(2, "Error: malloc failed for var value\n", 36);
	return (result);
}

static void	add_split_tokens_after(t_token *start, char **split, t_token *next)
{
	t_token	*last_new;
	t_token	*new;
	int		i;

	last_new = start;
	i = 1;
	while (split[i])
	{
		new = (t_token *)ft_calloc(1, sizeof(t_token));
		if (!new)
			break ;
		new->content = ft_strdup(split[i]);
		if (!new->content)
			return (free_mem(split));
		new->type = TOKEN_WORD;
		new->quote = 0;
		new->next = NULL;
		last_new->next = new;
		last_new = new;
		i++;
	}
	last_new->next = next;
}

void	split_token_if_needed(t_token *token)
{
	char	**split;
	t_token	*next;

	if (!token || !token->content)
		return ;
	if (token->quote == 0 && ft_strchr(token->content, ' '))
	{
		split = ft_split(token->content, ' ');
		if (!split)
			return ;
		if (!split[0] || split[0][0] == '\0')
			return (free_mem(split));
		next = token->next;
		free(token->content);
		token->content = ft_strdup(split[0]);
		if (!token->content)
			return (free_mem(split));
		add_split_tokens_after(token, split, next);
		free_mem(split);
	}
}