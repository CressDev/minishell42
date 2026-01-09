/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:44:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 22:56:56 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_word(t_fsm *fsm, char c, t_token **tokens)
{
	if ((c == ' ' || c == '\t' || c == '\0') && fsm->has_content)
	{
		create_token(fsm, tokens, 0);
		fsm->current_state = STATE_START;
		return (true);
	}
	else if (c == '|')
	{
		if (fsm->has_content)
			create_token(fsm, tokens, 0);
		fsm->current_state = STATE_PIPE;
		return (false);
	}
	else if (c == '\'')
	{
		fsm->current_state = STATE_SQUOTE;
		return (true);
	}
	else if (c == '\"')
	{
		fsm->current_state = STATE_DQUOTE;
		return (true);
	}
	token_append_char(fsm, c, tokens);
	return (true);
}
