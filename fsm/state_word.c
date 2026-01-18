/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:44:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/18 14:31:21 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	create_condition(t_fsm *fsm, char c, t_token **tokens)
{
	if ((c == ' ' || c == '\t' || c == '\0') && fsm->has_content
		&& !fsm->quote_flag)
	{
		create_token(fsm, tokens);
		fsm->current_state = STATE_START;
		return (true);
	}
	return (false);
}

bool	state_word(t_fsm *fsm, char c, t_token **tokens)
{
	if (create_condition(fsm, c, tokens))
		return (true);
	if (c == '|')
	{
		if (fsm->has_content)
			create_token(fsm, tokens);
		fsm->current_state = STATE_PIPE;
		return (false);
	}
	else if (c == '\'')
	{
		fsm->current_state = STATE_SQUOTE;
		return (false);
	}
	else if (c == '\"')
	{
		fsm->current_state = STATE_DQUOTE;
		return (false);
	}
	token_append_char(fsm, c, tokens);
	return (true);
}
