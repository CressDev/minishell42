/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:53:53 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 20:38:05 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_error(t_fsm *fsm, char c, t_token **tokens)
{
	char	*msg;

	(void)c;
	(void)tokens;
	msg = "\0";
	if (fsm->current_state == STATE_PIPE)
		msg = "minishell> unexpected EOF while looking for extra command \n";
	else if (fsm->current_state == STATE_DQUOTE
		|| fsm->current_state == STATE_SQUOTE)
		msg = "minishell> unexpected EOF while looking for a quote \n";
	else if (fsm->current_state == STATE_REDIRECT)
		msg = "minishell> unexpected EOF while looking for fd to redirect I/O \n";
	ft_putstr_fd(msg, 2);
	fsm->has_error = true;
	fsm->current_state = STATE_ERROR;
	free_tokens(tokens);
	destroy_fsm(&fsm);
	return (false);
}
