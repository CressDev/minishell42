/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_order.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:40:13 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/26 22:31:13 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles end-of-file (EOF) or empty input from the user.
 *
 * This function checks if the user input is NULL, indicating EOF or no input.
 * If the shell is running in interactive mode, it prints "exit" to the
 * corresponding file descriptor. Otherwise, it simply signals the main loop
 * to terminate or continue based on input presence.
 *
 * @param line Pointer to the string read from user input.
 * @param is_tty Non-zero if the shell is running in interactive mode.
 * @return true if EOF was detected or there is no user input (main loop
 * should terminate). false if input exists and the shell can continue normally.
 */
bool	handle_eof(char *line, int is_tty)
{
	if (!line)
	{
		if (is_tty)
			write(STDOUT_FILENO, "closing minishell\n", 19);
		return (true);
	}
	return (false);
}

/**
 * @brief Handles user interrupt signals (CTRL+C).
 *
 * This function checks if the global shell signal indicates an
 * interrupt (SIGINT). If so, it frees the input line and signals
 * the main loop to skip the current command.
 *
 * @param line Pointer to the input string read from the user entry.
 * @return true if an interrupt signal was detected and handled,
 * false if the shell can continue normal execution.
 */
bool	handle_interrupt(char *line)
{
	/*
	 * g_signal también se usa como exit status ($?).
	 * NO podemos comparar con SIGINT (2) porque muchos comandos fallan con 2
	 * (ej: `ls s`, `grep` sin patrón) y eso haría que el shell “ignore” comandos.
	 *
	 * Nuestro handler de señales setea g_signal=130 para Ctrl+C.
	 * El readline suele devolver una línea vacía tras Ctrl+C, así que solo
	 * descartamos ese caso.
	 */
	if (g_signal == 130 && line && line[0] == '\0')
	{
		free(line);
		return (true);
	}
	return (false);
}

/**
 * @brief Tokenizes the user input using a Finite State Machine (FSM).
 *
 * The FSM acts not only as a tokenizer but also as a syntax analyzer,
 * validating the input and preventing invalid parse elements from
 * propagating to later execution phases.
 *
 * @param line Pointer to the input string read from the user input.
 * @param tokens Pointer to a token list (initially NULL) that will be
 * populated with the generated tokens.
 *
 * @return true if tokenization succeeds, false if a syntax or allocation
 * error occurs.
 */
bool	obtain_tokens(char *line, t_token **tokens)
{
	entry_point(line, tokens);
	if (!*tokens)
	{
		free(line);
		return (false);
	}
	return (true);
}
