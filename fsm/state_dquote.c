/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:29:27 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/08 19:33:31 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_dquote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\"')
	{
		fsm->prev_state = fsm->current_state;
		fsm->counter++;
		if (fsm->counter == 2)
		{
			fsm->current_state = STATE_WORD;
			create_token(fsm, tokens, 2);
			fsm->counter = 0;
		}
		return (true);
	}
	else if (c == '\0')
	{
		error_handler(fsm, "dquote> ");
		free_tokens(tokens);
		default_state(fsm);
		return (false);
	}
	else
	{
		token_append_char(fsm, c, tokens);
		return (true);
	}
}
