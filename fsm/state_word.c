/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:44:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/16 14:22:56 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_state(t_fsm *fsm, t_state state, t_token **tokens)
{
	char	c;

	if (fsm->has_content)
	{
		create_token(fsm, tokens);
		fsm->has_content = false;
	}
	c = fsm->input[fsm->i_input + 1];
	if (c != '\0')
	{
		if (state == STATE_DQUOTE)
			fsm->current_state = STATE_DQUOTE;
		else if (state == STATE_SQUOTE)
			fsm->current_state = STATE_SQUOTE;
	}
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
		quote_state(fsm, STATE_SQUOTE, tokens);
		return (true);
	}
	else if (c == '\"')
	{
		quote_state(fsm, STATE_DQUOTE, tokens);
		return (true);
	}
	token_append_char(fsm, c, tokens);
	return (true);
}
