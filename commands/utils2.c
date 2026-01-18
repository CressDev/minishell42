/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:13:54 by cress             #+#    #+#             */
/*   Updated: 2026/01/18 13:48:28 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_in_range(t_token *start, t_token *end)
{
	int		argc;
	t_token	*tmp;
	t_token	*prev;

	argc = 0;
	tmp = start;
	prev = NULL;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN
			&& prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND
			&& prev->type != TOKEN_HEREDOC)))
			argc++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (argc);
}

void	fill_args_in_range(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token *tmp;
	t_token	*prev;
	int		i;

	tmp = start;
	prev = NULL;
	i = 0;
	while (tmp != end)
	{
		if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN
			&& prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND
			&& prev->type != TOKEN_HEREDOC)))
			cmd->args[i++] = ft_strdup(tmp->content);
		prev = tmp;
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
}
