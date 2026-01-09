/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:13:57 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/09 18:08:07 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fsm	*init_fsm(char *input)
{
	t_fsm	*fsm;

	fsm = malloc(sizeof(t_fsm));
	if (!fsm)
		return (NULL);
	ft_memset(fsm, 0, sizeof(t_fsm));
	fsm->token_capacity = 2;
	fsm->token = malloc(fsm->token_capacity);
	if (!fsm->token)
		return (destroy_fsm(&fsm), NULL);
	if (input)
	{
		fsm->input = ft_strdup(input);
		if (!fsm->input)
		{
			free(fsm);
			fsm = NULL;
			return (NULL);
		}
	}
	else
		fsm->input = NULL;
	return (fsm);
}

t_token_type	fsm_state_to_token_type(t_fsm *fsm)
{
	if (fsm->current_state == STATE_PIPE)
		return (TOKEN_PIPE);
	if (fsm->current_state == STATE_REDIRECT)
	{
		if (ft_strcmp(fsm->token, ">>") == 0)
			return (TOKEN_APPEND);
		if (ft_strcmp(fsm->token, "<<") == 0)
			return (TOKEN_HEREDOC);
		if (ft_strcmp(fsm->token, "<") == 0)
			return (TOKEN_REDIR_IN);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

void	create_token(t_fsm *fsm, t_token **tokens, int quoted)
{
	t_token	*new;

	if (fsm->i_token == 0)
		return ;
	fsm->token[fsm->i_token] = '\0';
	new = init_token(fsm, quoted);
	if (!new)
	{
		new = NULL;
		return ;
	}
	token_add_back(tokens, new);
	fsm->i_token = 0;
	fsm->token[0] = 0;
}

void	destroy_fsm(t_fsm **fsm)
{
	if (!fsm || !*fsm)
		return ;
	free((*fsm)->input);
	free((*fsm)->token);
	(*fsm)->input = NULL;
	(*fsm)->token = NULL;
	free(*fsm);
	*fsm = NULL;
}
