/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:56:09 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/20 23:51:43 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	redir_syntax_error(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == TOKEN_APPEND
			|| curr->type == TOKEN_HEREDOC
			|| curr->type == TOKEN_REDIR_IN
			|| curr->type == TOKEN_REDIR_OUT)
		{
			if (!curr->next)
				return ('\n');
			if (curr->next->type != TOKEN_WORD)
				return (curr->content[0]);
		}
		curr = curr->next;
	}
	return ('\0');
}

bool	state_redirect(t_fsm *fsm, char c, t_token **tokens)
{
	char	next;

	next = fsm->input[fsm->i_input + 1];
	if (c == '>' && next == '>')
		token_append_str(fsm, ">>", tokens);
	else if (c == '>')
		token_append_char(fsm, c, tokens);
	else if (c == '<' && next == '<')
		token_append_str(fsm, "<<", tokens);
	else if (c == '<')
		token_append_char(fsm, c, tokens);
	create_token(fsm, tokens);
	fsm->current_state = STATE_START;
	if ((c == '>' && next == '>') || (c == '<' && next == '<'))
		fsm->i_input++;
	return (true);
}
