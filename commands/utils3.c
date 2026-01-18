/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:38 by cress             #+#    #+#             */
/*   Updated: 2026/01/17 21:45:37 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredocs_in_range(t_token *start, t_token *end)
{
	t_token *tmp;
	int count;

	tmp = start;
	count = 0;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void fill_heredocs_in_range(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token *tmp;
	int i;

	tmp = start;
	i = 0;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_HEREDOC && tmp->next && tmp->next->type == TOKEN_WORD)
		{
			cmd->heredoc_delimiter[i] = ft_strdup(tmp->next->content);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->heredoc_delimiter[i] = NULL;
}
