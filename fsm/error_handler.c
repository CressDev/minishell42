/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:54:59 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 23:26:13 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(t_fsm *fsm, const char *line)
{
	char	*extra;
	char	*new_input;
	size_t	len;

	extra = readline(line);
	if (!extra)
	{
		fsm->current_state = STATE_ERROR;
		state_error(fsm, '\0', NULL);
		return ;
	}
	len = ft_strlen(fsm->input) + ft_strlen(extra) + 2;
	new_input = malloc(len);
	if (!new_input)
	{
		free(extra);
		return ;
	}
	ft_strlcpy(new_input, fsm->input, len);
	ft_strlcat(new_input, extra, len);
	free(extra);
	fsm->input = new_input;
}

void	default_state(t_fsm *fsm)
{
	fsm->i_len = ft_strlen(fsm->input);
	fsm->current_state = STATE_START;
	fsm->counter = 0;
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
