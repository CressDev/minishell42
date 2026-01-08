/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:56:09 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/08 20:01:17 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_redirect(t_fsm *fsm, char c, t_token **tokens)
{
	char	next;

	next = fsm->input[fsm->i_input + 1];
	if (c == '>' && next == '>')
		token_append_str(fsm, ">>", tokens);
	else if (c == '>')
		token_append_char(fsm, c, tokens);
	else if (c == '<' && next == '<')
		token_append_str(fsm, "<<", tokens);
	else if (c == '<')
		token_append_char(fsm, c, tokens);
	else
	{
		fsm->current_state = STATE_ERROR;
		state_error(fsm, c, NULL);
		return (false);
	}
	create_token(fsm, tokens, 0);
	fsm->current_state = STATE_START;
	if ((c == '>' && next == '>') || (c == '<' && next == '<'))
		fsm->i_input++;
	return (true);
}
