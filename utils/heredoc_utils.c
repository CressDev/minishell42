/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:13:54 by cress             #+#    #+#             */
/*   Updated: 2026/01/19 11:48:56 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_in_range(t_token *start, t_token *end)
{
	int		argc;
	t_token	*tmp;
	t_token	*prev;

	argc = 0;
	tmp = start;
	prev = NULL;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN
					&& prev->type != TOKEN_REDIR_OUT
					&& prev->type != TOKEN_APPEND
					&& prev->type != TOKEN_HEREDOC)))
			argc++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (argc);
}

void	fill_args_in_range(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;

	tmp = start;
	prev = NULL;
	i = 0;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN
					&& prev->type != TOKEN_REDIR_OUT
					&& prev->type != TOKEN_APPEND
					&& prev->type != TOKEN_HEREDOC)))
			cmd->args[i++] = ft_strdup(tmp->content);
		prev = tmp;
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
}

int	count_heredocs_in_range(t_token *start, t_token *end)
{
	t_token	*tmp;
	int		count;

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

void	fill_heredocs(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*tmp;
	int		i;

	tmp = start;
	i = 0;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_HEREDOC
			&& tmp->next
			&& tmp->next->type == TOKEN_WORD)
		{
			cmd->heredoc_delimiter[i] = ft_strdup(tmp->next->content);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->heredoc_delimiter[i] = NULL;
}
