/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:33:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/16 13:52:40 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_squote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\'')
	{
		fsm->prev_state = STATE_SQUOTE;
		fsm->current_state = STATE_WORD;
		return (true);
	}
	if (c == '\0' && fsm->token)
	{
		error_user_input(fsm, "quote> ");
		free_tokens(tokens);
		default_state(fsm);
		return (false);
	}
	if (c == '\n')
	{
		token_append_char(fsm, c, tokens);
		return (true);
	}
	token_append_char(fsm, c, tokens);
	return (true);
}
