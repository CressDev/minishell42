/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:56:09 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 20:37:08 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_handler(t_fsm *fsm)
{
	size_t	i;

	i = 0;
	while (fsm->input[i] == ' ')
		i++;
    if (fsm->input[i] == '\0' || fsm->input[i] == '\n')
    {
        fsm->current_state = STATE_ERROR;
        state_error(fsm, '\0', NULL);
        return (false);
    }
    return (true);
}

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
	if (!error_handler(fsm))
		return (false);
	fsm->current_state = STATE_START;
	if ((c == '>' && next == '>') || (c == '<' && next == '<'))
		fsm->i_input++;
	return (true);
}
