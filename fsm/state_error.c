/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:53:53 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/22 01:18:19 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_error(t_fsm *fsm, char c, t_token **tokens)
{
	(void)tokens;
	if (c == '|')
	{
		write(2, "parse error near |\n", 20);
		free_tokens(tokens);
		destroy_fsm(&fsm);
		return (true);
	}
	fsm->has_error = true;
	fsm->current_state = STATE_ERROR;
	return (false);
}
