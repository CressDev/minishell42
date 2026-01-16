/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:37:14 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/16 11:19:02 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_end(t_fsm *fsm, char c, t_token **tokens)
{
	if (c == '\0' || c == '\n')
	{
		create_token(fsm, tokens);
		fsm->prev_state = fsm->current_state;
		fsm->current_state = STATE_END;
	}
	return (true);
}
