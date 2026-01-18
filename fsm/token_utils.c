/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:01:53 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/18 14:31:32 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_fsm *fsm, int quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->type = fsm_state_to_token_type(fsm);
	token->quote = quoted;
	if (fsm->token[0] != '\0' && fsm->token[0] != '\n')
	{
		token->content = ft_strdup(fsm->token);
		if (!token->content)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->content = NULL;
	return (token);
}

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !new)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	token_append_str(t_fsm *fsm, const char *str, t_token **tokens)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	if (fsm->i_token + len >= fsm->token_capacity)
		expand_token_buffer(fsm, tokens);
	while (i < len)
		fsm->token[fsm->i_token++] = str[i++];
	fsm->token[fsm->i_token] = '\0';
	fsm->has_content = true;
}

void	token_append_char(t_fsm *fsm, const char c, t_token **tokens)
{
	if (fsm->i_token + 1 >= fsm->token_capacity)
		expand_token_buffer(fsm, tokens);
	if (c != '\0')
		fsm->token[fsm->i_token++] = c;
	fsm->token[fsm->i_token] = '\0';
	fsm->has_content = (fsm->i_token > 0);
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*current;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = tmp;
	}
	*tokens = NULL;
}
