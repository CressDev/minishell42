/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:40:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/17 21:44:51 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_cmds_redir(t_cmd **current, t_token **token)
{
	token_redirect(*current, *token);
	if ((*token)->next)
		*token = (*token)->next;
}

void	build_cmds_word(t_cmd **head, t_cmd **current, t_token **token, t_envs *envs)
{
	*current = token_word(*current, *token, envs);
	if (!*head)
		*head = *current;
	if (*current)
		(*current)->argc++;
}

void	build_cmds_step(t_cmd **head, t_cmd **current, t_token **token, t_envs *envs)
{
	expand_token(*token, envs);
	if ((*token)->type == TOKEN_WORD)
		build_cmds_word(head, current, token, envs);
	else if ((*token)->type == TOKEN_PIPE)
		*current = token_pipe(envs, *current);
	else if ((*token)->type == TOKEN_REDIR_IN || (*token)->type == TOKEN_REDIR_OUT
		|| (*token)->type == TOKEN_APPEND || (*token)->type == TOKEN_HEREDOC)
		build_cmds_redir(current, token);
	expand_token(*token, envs);
	*token = (*token)->next;
}

void	build_cmds_loop(t_cmd **head, t_cmd **current, t_token **token, t_envs *envs)
{
	while (*token)
		build_cmds_step(head, current, token, envs);
}

t_cmd	*parse_tokens(t_token *token, t_envs *envs)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token *token_list;

	head = NULL;
	current = NULL;
	token_list = token;
	build_cmds_loop(&head, &current, &token, envs);
	assign_args_heredocs_loop(head, token_list);
	return head;
}
