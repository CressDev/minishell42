/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:21:52 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/22 00:40:43 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fsm_dispatcher(t_fsm *fsm, t_token **tokens)
{
	char		c;
	bool		consume;
	static bool	(*g_handlers[8])(t_fsm *, char, t_token **) = {
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
	t_token	*error_tok;

	*tokens = NULL;
	fsm = init_fsm(input);
	if (!fsm)
		return ;
	fsm_dispatcher(fsm, tokens);
	if (pipe_syntax_error(tokens))
		return (state_error(fsm, '|', tokens), (void)0);
	while (pipe_is_incomplete(tokens))
	{
		error_user_input(fsm, "pipe> ");
		default_state(fsm);
		fsm_dispatcher(fsm, tokens);
	}
	error_tok = redir_syntax_error(tokens);
	if (error_tok)
	{
		show_syntax(fsm, error_tok, tokens);
		return ;
	}
	destroy_fsm(&fsm);
}
