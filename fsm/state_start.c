/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:39:17 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/08 19:44:03 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state	next_state_from_start(char c)
{
	if (c == ' ' || c == '\t')
		return (STATE_START);
	else if (c == '|')
		return (STATE_PIPE);
	else if (c == '>' || c == '<')
		return (STATE_REDIRECT);
	else if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '\"')
		return (STATE_DQUOTE);
	return (STATE_WORD);
}

bool	state_start(t_fsm *fsm, char c, t_token **tokens)
{
	t_state	new_state;

	(void)tokens;
	new_state = next_state_from_start(c);
	if (new_state == STATE_START)
	{
		fsm->prev_state = fsm->current_state;
		fsm->current_state = STATE_START;
		return (true);
	}
	fsm->current_state = new_state;
	return (false);
}
