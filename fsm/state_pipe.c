/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:48:56 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/22 01:22:57 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipe_syntax_error(t_token **tokens)
{
	t_token	*prev;
	t_token	*current;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!prev)
				return (true);
			if (current->next && current->next->type == TOKEN_PIPE)
				return (true);
		}
		prev = current;
		current = current->next;
	}
	return (false);
}

bool	pipe_is_incomplete(t_token **tokens)
{
	t_token	*last;

	if (!tokens || !*tokens)
		return (false);
	last = *tokens;
	while (last->next)
		last = last->next;
	return (last->type == TOKEN_PIPE);
}

bool	state_pipe(t_fsm *fsm, char c, t_token **tokens)
{
	if (c != '|')
		return (false);
	token_append_char(fsm, c, tokens);
	create_token(fsm, tokens);
	fsm->current_state = STATE_START;
	return (true);
}
