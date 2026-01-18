/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:40:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/18 14:18:13 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_redir(t_cmd **cmd, t_token **token)
{
	token_redirect(*cmd, *token);
	if ((*token)->next)
		*token = (*token)->next;
}

static void	cmd_words(t_cmd **head, t_cmd **cmd, t_token **token, t_envs *envs)
{
	*cmd = token_word(*cmd, *token, envs);
	if (!*head)
		*head = *cmd;
	if (*cmd)
		(*cmd)->argc++;
}

static void	cmd_step(t_cmd **head, t_cmd **cmd, t_token **token, t_envs *envs)
{
	expand_token(*token, envs);
	if ((*token)->type == TOKEN_WORD)
		cmd_words(head, cmd, token, envs);
	else if ((*token)->type == TOKEN_PIPE)
		*cmd = token_pipe(envs, *cmd);
	else if ((*token)->type == TOKEN_REDIR_IN
		|| (*token)->type == TOKEN_REDIR_OUT
		|| (*token)->type == TOKEN_APPEND
		|| (*token)->type == TOKEN_HEREDOC)
		cmd_redir(cmd, token);
	*token = (*token)->next;
}

t_cmd	*parse_tokens(t_token *token, t_envs *envs)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*token_list;

	head = NULL;
	cmd = NULL;
	token_list = token;
	while (token)
		cmd_step(&head, &cmd, &token, envs);
	assign_args_heredocs_loop(head, token_list);
	return (head);
}
