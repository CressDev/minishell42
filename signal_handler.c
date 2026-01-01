/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:21:38 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 15:49:20 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctlc_continuation(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		g_signal = 130;
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		if (get_in_readline_state())
		{
			rl_on_new_line();
			rl_redisplay();
		}
		g_signal = 130;
	}
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
		g_signal = 130;
	}
}

void	sigint_wait_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 130;
}

void	install_sigint_wait_handler(struct sigaction *old)
{
	struct sigaction	sa_new;

	sa_new.sa_handler = sigint_wait_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, old);
}
