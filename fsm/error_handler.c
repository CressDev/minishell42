/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:54:59 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/23 17:18:18 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*error_readline_handler(t_fsm *fsm, const char *line)
{
	char	*extra;

	signal(SIGINT, &signal_ctlc_continuation);
	extra = readline(line);
	signal(SIGINT, &signal_handler);
	if (!extra || g_signal == 130)
	{
		if (extra)
			free(extra);
		fsm->current_state = STATE_ERROR;
		fsm->has_error = true;
		g_signal = 0;
		return (NULL);
	}
	return (extra);
}

bool	error_user_input(t_fsm *fsm, const char *line)
{
	char	*extra;
	char	*new_input;
	size_t	len;

	extra = error_readline_handler(fsm, line);
	if (!extra)
		return (false);
	len = ft_strlen(fsm->input) + ft_strlen(extra) + 2;
	new_input = malloc(len);
	if (!new_input)
	{
		free(extra);
		return (false);
	}
	ft_strlcpy(new_input, fsm->input, len);
	ft_strlcat(new_input, "\n", len);
	ft_strlcat(new_input, extra, len);
	free(extra);
	free(fsm->input);
	fsm->input = new_input;
	return (true);
}

void	default_state(t_fsm *fsm)
{
	fsm->i_len = ft_strlen(fsm->input);
	fsm->current_state = STATE_START;
	fsm->quote_flag = false;
	fsm->i_token = 0;
	fsm->i_input = 0;
}

void	expand_token_buffer(t_fsm *fsm, t_token **tokens)
{
	size_t	new_size;
	char	*new_buffer;

	new_size = fsm->token_capacity * 2;
	new_buffer = malloc(new_size);
	if (!new_buffer)
	{
		destroy_fsm(&fsm);
		free_tokens(tokens);
		write(2, "minishell: memory allocation error\n", 35);
		exit(1);
	}
	ft_memcpy(new_buffer, fsm->token, fsm->i_token);
	free(fsm->token);
	fsm->token = new_buffer;
	fsm->token_capacity = new_size;
}
