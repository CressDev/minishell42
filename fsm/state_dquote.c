/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:29:27 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 22:48:04 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_dquote(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\"')
	{
		fsm->current_state = STATE_WORD;
		return (true);
	}
	if (c == '\0')
	{
		error_handler(fsm, "dquote> ");
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
