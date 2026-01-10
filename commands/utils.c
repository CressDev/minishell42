/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:10:15 by amonteag          #+#    #+#             */
/*   Updated: 2026/01/10 17:55:29 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_envs *envs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->envs = envs;
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_tokens(t_token *token, t_envs *envs)
{
	t_cmd	*head;
	t_cmd	*current;

	head = NULL;
	current = NULL;
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			current = token_word(envs, current, token);
			if (!head)
				head = current;
		}
		else if (token->type == TOKEN_PIPE)
			current = token_pipe(envs, current);
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
			token_redirect(current, token);
		token = token->next;
	}
	return (head);
}
