/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:16:26 by cress             #+#    #+#             */
/*   Updated: 2025/12/28 23:47:48 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int saved_stdin, int saved_stdout, int input_fd,
				int output_fd)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
}

int	count_args_no_redirect(char **tokens)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0
			|| ft_strcmp(tokens[i], "<<") == 0)
		{
			if (!tokens[i + 1])
				return (-1);
			i += 2;
		}
		else
		{
			arg_count++;
			i++;
		}
	}
	return (arg_count);
}

void	fill_args_array(t_cmd *cmd, char **tokens)
{
	int	i;
	int	arg_i;

	i = 0;
	arg_i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0
			|| ft_strcmp(tokens[i], "<<") == 0)
		{
			if (!tokens[i + 1])
				return ;
			i += 2;
		}
		else
		{
			cmd->args[arg_i] = ft_strdup(tokens[i]);
			if (!cmd->args[arg_i])
				return ;
			arg_i++;
			i++;
		}
	}
	cmd->args[arg_i] = NULL;
}

t_cmd	*parse_redirections(char **tokens)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->args = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->next = NULL;
	arg_count = count_args_no_redirect(tokens);
	if (arg_count == -1)
		return (free_redirect(cmd), write(2, "syntax error\n", 13), NULL);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
		return (free_redirect(cmd), NULL);
	if (process_redirections(cmd, tokens) == -1)
		return (free_redirect(cmd), NULL);
	fill_args_array(cmd, tokens);
	return (cmd);
}
