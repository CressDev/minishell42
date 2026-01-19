/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:21:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/19 09:30:30 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fsm_dispatcher(t_fsm *fsm, t_token **tokens)
{
	char					c;
	bool					consume;
	static t_handler	g_handlers[] = {
		state_start,
		state_word,
		state_squote,
		state_dquote,
		state_pipe,
		state_redirect,
		state_error,
		state_end,
	};

	fsm->i_len = ft_strlen(fsm->input);
	while (fsm->i_input <= fsm->i_len)
	{
		if (fsm->current_state == STATE_ERROR)
			return ;
		c = fsm->input[fsm->i_input];
		consume = g_handlers[fsm->current_state](fsm, c, tokens);
		if (consume)
			fsm->i_input++;
	}
	if (!fsm->has_error)
		state_end(fsm, '\0', tokens);
}

/**
 * @brief Controls the Finite State Machine (FSM) for tokenization.
 *
 * This function initializes the FSM to perform lexical analysis
 * of the user input. The FSM uses a function pointer array (dispatcher) indexed
 * by an enum representing each state, allowing the FSM to transition through
 * the different parsing states automatically.
 *
 * @param input Pointer to the string read from user input.
 * @param tokens Pointer to a pointer to the token list where the generated
 * tokens will be stored.
 */
void	entry_point(char *input, t_token **tokens)
{
	t_fsm	*fsm;

	*tokens = NULL;
	fsm = init_fsm(input);
	if (!fsm)
		return ;
	fsm_dispatcher(fsm, tokens);
	destroy_fsm(&fsm);
}
