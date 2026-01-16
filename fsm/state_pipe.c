/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:48:56 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/16 11:21:07 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_pipe(t_fsm *fsm, char c, t_token **tokens)
{
	size_t	tmp;

	if (c != '|')
		return (false);
	token_append_char(fsm, c, tokens);
	create_token(fsm, tokens);
	tmp = fsm->i_input + 1;
	while (fsm->input[tmp] == ' ' || fsm->input[tmp] == '\t'
		|| fsm->input[tmp] == '\n')
		tmp++;
	if (fsm->input[tmp] == '\0')
	{
		error_user_input(fsm, "pipe> ");
		free_tokens(tokens);
		default_state(fsm);
		*tokens = NULL;
		return (false);
	}
	fsm->current_state = STATE_START;
	return (true);
}
