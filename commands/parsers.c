/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:47:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/18 13:45:53 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*token_word(t_cmd *current, t_token *token, t_envs *envs)
{
	(void)token;
	if (!current)
	{
		current = init_cmd(envs);
		if (!current)
			return (NULL);
	}
	return (current);
}

t_cmd	*token_pipe(t_envs *envs, t_cmd *current)
{
	if (!current)
		return (NULL);
	current->next = init_cmd(envs);
	return (current->next);
}

void	token_redirect(t_cmd *current, t_token *token)
{
	int	fd;

	if (!current || !token || !token->next)
		return ;
	if (token->type == TOKEN_REDIR_IN)
		current->input_file = ft_strdup(token->next->content);
	else if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
	{
		if (current->output_file)
		{
			fd = open(current->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
				close(fd);
			free(current->output_file);
		}
		current->output_file = ft_strdup(token->next->content);
		current->append = 0;
		if (token->type == TOKEN_APPEND)
			current->append = 1;
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		if (!token->next || token->next->type != TOKEN_WORD)
			write(STDIN_FILENO, "Syntax error.\n", 15);
	}
}
