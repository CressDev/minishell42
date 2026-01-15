/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:44:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/15 19:02:27 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_state(t_fsm *fsm, t_state state)
{
	fsm->has_content = true;
	if (state == STATE_DQUOTE)
		fsm->current_state = STATE_DQUOTE;
	else if (state == STATE_SQUOTE)
		fsm->current_state = STATE_SQUOTE;
}

bool	state_word(t_fsm *fsm, char c, t_token **tokens)
{
	if ((c == ' ' || c == '\t' || c == '\0') && fsm->has_content)
	{
		create_token(fsm, tokens);
		fsm->current_state = STATE_START;
		return (true);
	}
	else if (c == '|')
	{
		if (fsm->has_content)
			create_token(fsm, tokens);
		fsm->current_state = STATE_PIPE;
		return (false);
	}
	else if (c == '\'')
	{
		quote_state(fsm, STATE_SQUOTE);
		return (true);
	}
	else if (c == '\"')
	{
		quote_state(fsm, STATE_DQUOTE);
		return (true);
	}
	token_append_char(fsm, c, tokens);
	return (true);
}
