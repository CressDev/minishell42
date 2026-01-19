/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 11:28:36 by cress             #+#    #+#             */
/*   Updated: 2026/01/19 12:00:52 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_continuation_signal_handler(struct sigaction *old_sa)
{
	struct sigaction	sa;

	sa.sa_handler = signal_ctlc_continuation;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_sa);
}

void	restore_signal_handler(struct sigaction *old_sa)
{
	sigaction(SIGINT, old_sa, NULL);
}

int	*get_in_readline_state_ptr(void)
{
	static int	in_readline = 0;

	return (&in_readline);
}

int	get_in_readline_state(void)
{
	return (*get_in_readline_state_ptr());
}

void	set_in_readline_state(int state)
{
	*get_in_readline_state_ptr() = state;
}
