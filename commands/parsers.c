/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:47:40 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/17 20:21:59 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	add_arg(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
	}
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return (-1);
	j = 0;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		cmd->args[j] = NULL; // Evita doble free
		j++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		return (-1);
	}
	if (cmd->args)
		free(cmd->args); // solo liberar el array, no los strings (ya movidos)
	cmd->args = new_args;
	return (0);
}
*/
/*static int	add_heredoc(t_cmd *cmd, char *delimeter)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	if (cmd->heredoc_delimiter)
		while (cmd->heredoc_delimiter[i])
			i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (-1);
	j = 0;
	while (j < i)
	{
		new[j] = cmd->heredoc_delimiter[j];
		j++;
	}
	new[i] = ft_strdup(delimeter);
	if (!new[i])
	{
		free(new);
		return (-1);
	}
	if (cmd->heredoc_delimiter)
	{
		int k = 0;
		while (cmd->heredoc_delimiter[k])
			free(cmd->heredoc_delimiter[k++]);
		free(cmd->heredoc_delimiter);
	}
	cmd->heredoc_delimiter = new;
	return (0);
}
*/
t_cmd	*token_word(t_cmd *current, t_token *token, t_envs *envs)
{
	(void)token;
	if (!current)
	{
		current = init_cmd(envs);
		if (!current)
			return (NULL);
	}
	// Ya no se añade el argumento aquí, se hace en la doble pasada de parse_tokens
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
	int fd;

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
		/*if (add_heredoc(current, token->next->content) == -1)
			write(STDIN_FILENO, "Malloc error", 13);*/
	}
}
