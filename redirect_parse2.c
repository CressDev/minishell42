/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:27:13 by cress             #+#    #+#             */
/*   Updated: 2026/01/01 10:31:59 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_output_redirect(t_cmd *cmd, char **tokens, int i)
{
	int	fd;

	if (ft_strcmp(tokens[i], ">>") == 0)
		cmd->append = 1;
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = ft_strdup(tokens[i + 1]);
	if (!cmd->output_file)
	{
		ft_printf("Error: malloc failed for output file\n");
		return ;
	}
	fd = open(cmd->output_file, O_CREAT | O_WRONLY, 0644);
	if (fd != -1)
		close(fd);
}

static void	handle_heredoc_cleanup(t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		free(line);
	}
	free(cmd->heredoc_delimiter);
}

int	process_input_redirect(t_cmd *cmd, char **tokens, int i)
{
	int	fd;

	if (ft_strcmp(tokens[i], "<") == 0)
	{
		fd = open(tokens[i + 1], O_RDONLY);
		if (fd == -1)
			return (write(2, "no such file or directory\n", 26), -1);
		close(fd);
		if (cmd->input_file)
			free(cmd->input_file);
		cmd->input_file = ft_strdup(tokens[i + 1]);
		if (!cmd->input_file)
			ft_printf("Error: malloc failed for input file\n");
		return (0);
	}
	else if (ft_strcmp(tokens[i], "<<") == 0)
	{
		if (cmd->is_heredoc)
			handle_heredoc_cleanup(cmd);
		cmd->heredoc_delimiter = ft_strdup(tokens[i + 1]);
		if (!cmd->heredoc_delimiter)
			ft_printf("Error: malloc failed for heredoc\n");
		cmd->is_heredoc = 1;
	}
	return (0);
}

int	process_redirections(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
		{
			process_output_redirect(cmd, tokens, i);
			i += 2;
		}
		else if (ft_strcmp(tokens[i], "<") == 0
			|| ft_strcmp(tokens[i], "<<") == 0)
		{
			if (process_input_redirect(cmd, tokens, i) == -1)
				return (-1);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}
