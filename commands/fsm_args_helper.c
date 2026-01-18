/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_args_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:30:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/18 13:56:44 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_no_redirect_fsm(t_token *token)
{
	int		count;
	t_token	*prev;

	count = 0;
	prev = NULL;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD && (!prev
				|| (prev->type != TOKEN_REDIR_IN
					&& prev->type != TOKEN_REDIR_OUT
					&& prev->type != TOKEN_APPEND
					&& prev->type != TOKEN_HEREDOC)))
			count++;
		prev = token;
		token = token->next;
	}
	return (count);
}

void	fill_args_array_fsm(t_cmd *cmd, t_token *token)
{
	int		i;
	t_token	*prev;

	i = 0;
	prev = NULL;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD && (!prev
				|| (prev->type != TOKEN_REDIR_IN
					&& prev->type != TOKEN_REDIR_OUT
					&& prev->type != TOKEN_APPEND
					&& prev->type != TOKEN_HEREDOC)))
		{
			cmd->args[i] = ft_strdup(token->content);
			i++;
		}
		prev = token;
		token = token->next;
	}
	cmd->args[i] = NULL;
}

int	count_heredoc_delims_fsm(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_HEREDOC
			&& token->next && token->next->type == TOKEN_WORD)
			count++;
		token = token->next;
	}
	return (count);
}

void	fill_heredoc_delims_fsm(t_cmd *cmd, t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_HEREDOC && token->next
			&& token->next->type == TOKEN_WORD)
		{
			cmd->heredoc_delimiter[i] = ft_strdup(token->next->content);
			i++;
		}
		token = token->next;
	}
	if (cmd->heredoc_delimiter)
		cmd->heredoc_delimiter[i] = NULL;
}
