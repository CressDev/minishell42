/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:53:53 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/21 00:27:00 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_error(char c)
{
	write(2, "parse error near ", 18);
	if (c == '\n')
		write(2, "newline", 7);
	else
		write(2, &c, 1);
	write(2, "\n", 1);
}

bool	state_error(t_fsm *fsm, char c, t_token **tokens)
{
	(void)tokens;
	write_error(c);
	fsm->has_error = true;
	fsm->current_state = STATE_ERROR;
	if (tokens)
		free_tokens(tokens);
	destroy_fsm(&fsm);
	return (false);
}
