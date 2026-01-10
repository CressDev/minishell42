/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 20:32:42 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 15:40:15 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
