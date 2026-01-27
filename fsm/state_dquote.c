/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:29:27 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/27 20:20:32 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	void_create(t_fsm *fsm, t_token **tokens)
{
	fsm->prev_state = STATE_DQUOTE;
	fsm->current_state = STATE_WORD;
	create_token(fsm, tokens);
	fsm->current_state = STATE_START;
	fsm->quote_flag = false;
}

bool	state_dquote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\"' && fsm->quote_flag)
	{
		void_create(fsm, tokens);
		return (true);
	}
	else if (c == '\"' && !fsm->quote_flag)
	{
		fsm->quote_flag = true;
		return (true);
	}
	else if (c == '\0' && fsm->quote_flag)
	{
		state_error(fsm, '\"', tokens);
		return (false);
	}
	else
	{
		token_append_char(fsm, c, tokens);
		return (true);
	}
}
