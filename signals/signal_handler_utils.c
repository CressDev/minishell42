/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 11:28:36 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 11:28:43 by amonteag         ###   ########.fr       */
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
