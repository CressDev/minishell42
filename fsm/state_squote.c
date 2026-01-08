/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:33:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/08 19:36:56 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_squote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\'')
	{
		fsm->current_state = fsm->prev_state;
		fsm->counter++;
		if (fsm->counter == 2)
		{
			fsm->current_state = STATE_WORD;
			create_token(fsm, tokens, 1);
			fsm->counter = 0;
		}
		return (true);
	}
	else if (c == '\0')
	{
		error_handler(fsm, "quote> ");
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
