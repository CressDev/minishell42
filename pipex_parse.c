/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:54:50 by cress             #+#    #+#             */
/*   Updated: 2025/12/28 13:17:55 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	direct_execute(t_list **env, char **tokens, char **environ)
{
	char	*full_path;

	if (!tokens[0] || tokens[0][0] == '\0')
		return (write(STDERR_FILENO, " : command not found\n", 22),
			exit(127), (void)0);
	full_path = find_command_in_path(tokens[0], *env);
	if (!full_path)
	{
		write(STDERR_FILENO, tokens[0], ft_strlen(tokens[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(full_path, tokens, environ);
	perror("execve failed");
	exit(126);
}

char	**create_cmd_tokens(char **tokens, int start, int end)
{
	char	**cmd_tokens;
	int		count;
	int		i;

	count = end - start;
	if (count <= 0)
		return (NULL);
	cmd_tokens = malloc(sizeof(char *) * (count + 1));
	if (!cmd_tokens)
		return (NULL);
	i = 0;
	while (start < end)
	{
		cmd_tokens[i] = tokens[start];
		i++;
		start++;
	}
	cmd_tokens[i] = NULL;
	return (cmd_tokens);
}

t_cmd	*add_cmd_to_pipeline(char **tokens, int start, int end)
{
	t_cmd	*new_cmd;
	char	**cmd_tokens;

	cmd_tokens = create_cmd_tokens(tokens, start, end);
	if (!cmd_tokens)
		return (NULL);
	new_cmd = parse_redirections(cmd_tokens);
	free(cmd_tokens);
	if (!new_cmd)
		return (NULL);
	return (new_cmd);
}

void	list_pipeline(t_cmd	**first_cmd, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!new_cmd)
		return ((void)0);
	if (!*first_cmd)
		return (*first_cmd = new_cmd, (void)0);
	current = *first_cmd;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

t_cmd	*parse_pipeline(char **tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*new_cmd;
	int		start;
	int		end;
	int		i;

	start = 0;
	i = 0;
	first_cmd = NULL;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0 || !tokens[i + 1])
		{
			if (ft_strcmp(tokens[i], "|") == 0)
				end = i;
			else
				end = i + 1;
			new_cmd = add_cmd_to_pipeline(tokens, start, end);
			list_pipeline(&first_cmd, new_cmd);
			start = i + 1;
		}
		i++;
	}
	return (first_cmd);
}
