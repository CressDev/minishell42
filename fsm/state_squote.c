/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:33:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/28 23:39:18 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	void_create(t_fsm *fsm)
{
	fsm->prev_state = STATE_SQUOTE;
	fsm->current_state = STATE_START;
	fsm->quote_flag = false;
}

bool	state_squote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\'' && fsm->quote_flag)
	{
		void_create(fsm);
		return (true);
	}
	else if (c == '\'' && !fsm->quote_flag)
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
