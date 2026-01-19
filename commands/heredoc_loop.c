/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:30:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/19 12:56:11 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_args_heredocs(t_cmd *cmd, t_token *start, t_token *end)
{
	int	hcount;

	hcount = count_heredocs_in_range(start, end);
	if (hcount > 0)
	{
		cmd->heredoc_delimiter = ft_calloc(hcount + 1, sizeof(char *));
		fill_heredocs(cmd, start, end);
		cmd->is_heredoc = 1;
	}
}

static void	assign_args_heredocs_args(t_cmd *cmd, t_token *start, t_token *end)
{
	int	argc;

	argc = count_args_in_range(start, end);
	cmd->args = ft_calloc(argc + 1, sizeof(char *));
	fill_args_in_range(cmd, start, end);
}

static void	assign_args_heredocs_step(t_cmd *cmd, t_token **tok_iter)
{
	t_token	*start;
	t_token	*end;

	start = *tok_iter;
	end = *tok_iter;
	while (end && end->type != TOKEN_PIPE)
		end = end->next;
	assign_args_heredocs_args(cmd, start, end);
	assign_args_heredocs(cmd, start, end);
	if (end && end->type == TOKEN_PIPE)
		*tok_iter = end->next;
	else
		*tok_iter = end;
}

void	assign_args_heredocs_loop(t_cmd *head, t_token *token_list)
{
	t_cmd	*cmd_iter;
	t_token	*tok_iter;

	cmd_iter = head;
	tok_iter = token_list;
	while (cmd_iter)
	{
		assign_args_heredocs_step(cmd_iter, &tok_iter);
		cmd_iter = cmd_iter->next;
	}
}
