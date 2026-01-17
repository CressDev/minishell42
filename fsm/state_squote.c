/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:33:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/17 18:17:24 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	inner_quote(t_fsm *fsm, char c, char quote_type)
{
	if (c == quote_type)
	{
		fsm->quote_flag = !fsm->quote_flag;
		if (quote_type == '\'')
			fsm->prev_state = STATE_SQUOTE;
		else
			fsm->prev_state = STATE_DQUOTE;
		return (true);
	}
	return (false);
}

bool	state_squote(t_fsm *fsm, char c, t_token **tokens)
{
	if (inner_quote(fsm, c, '\''))
		return (true);
	if (c == '\0')
	{
		if (fsm->quote_flag)
		{
			error_user_input(fsm, "quote> ");
			free_tokens(tokens);
			default_state(fsm);
			return (false);
		}
		else
		{
			fsm->current_state = STATE_WORD;
			fsm->prev_state = STATE_SQUOTE;
		}
		return (false);
	}
	if (fsm->quote_flag)
		token_append_char(fsm, c, tokens);
	return (true);
}
