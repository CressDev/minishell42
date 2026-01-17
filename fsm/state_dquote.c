/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:29:27 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/17 18:47:38 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	inner_quote(t_fsm *fsm, char c, char quote_type)
{
	if (c != quote_type)
		return (false);
	if (!fsm->quote_flag)
	{
		if ((quote_type == '\"' && fsm->prev_state == STATE_DQUOTE)
			|| (quote_type == '\'' && fsm->prev_state == STATE_SQUOTE))
			return (true);
		fsm->quote_flag = true;
		if (quote_type == '\"')
			fsm->prev_state = STATE_DQUOTE;
		else
			fsm->prev_state = STATE_SQUOTE;
		return (true);
	}
	if (fsm->quote_flag)
	{
		fsm->quote_flag = false;
		fsm->current_state = STATE_WORD;
		if (quote_type == '\"')
			fsm->prev_state = STATE_DQUOTE;
		else
			fsm->prev_state = STATE_SQUOTE;
		return (true);
	}
	return (false);
}

bool	state_dquote(t_fsm *fsm, char c, t_token **tokens)
{
	if (inner_quote(fsm, c, '\"'))
		return (true);
	if (c == '\0')
	{
		if (fsm->quote_flag)
		{
			error_user_input(fsm, "dquote> ");
			free_tokens(tokens);
			default_state(fsm);
			return (false);
		}
		else
		{
			fsm->current_state = STATE_WORD;
			fsm->prev_state = STATE_DQUOTE;
		}
		return (false);
	}
	if (fsm->quote_flag)
		token_append_char(fsm, c, tokens);
	return (true);
}
