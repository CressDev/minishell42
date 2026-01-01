/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:31:48 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 11:19:59 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(t_list **env, char **tokens)
{
	if (!tokens || !tokens[0])
		return (false);
	if (ft_strcmp(tokens[0], "env") == 0)
		return (env_command(*env, tokens), true);
	if (ft_strcmp(tokens[0], "pwd") == 0)
		return (pwd_command(), true);
	if (ft_strcmp(tokens[0], "unset") == 0)
		return (unset_command(env, tokens), true);
	if (ft_strcmp(tokens[0], "exit") == 0)
		return (exit_command(tokens), true);
	if (ft_strcmp(tokens[0], "export") == 0)
		return (export_command(env, tokens), true);
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (echo_command(tokens), true);
	if (ft_strcmp(tokens[0], "cd") == 0)
		return (cd_command(env, tokens), true);
	return (false);
}

static void	exec_redirection_cmd(char **tokens, t_list **env, char **environ,
								int is_tty)
{
	t_cmd	*cmd;

	cmd = parse_redirections(tokens);
	if (cmd)
	{
		exec_redir(cmd, env, environ, is_tty);
		free_redirect(cmd);
	}
}

static void	exec_pipeline_cmd(char **tokens, t_list **env, char **environ,
							int is_tty)
{
	t_cmd	*cmd;

	cmd = parse_pipeline(tokens);
	if (cmd)
	{
		execute_pipeline(cmd, env, environ, is_tty);
		free_pipeline(cmd);
	}
}

void	exec_parsed_cmd(char **tokens, t_list **env, char **environ,
					int is_tty)
{
	if (!validate_pipe_syntax(tokens))
		return ;
	if (has_pipes(tokens))
		exec_pipeline_cmd(tokens, env, environ, is_tty);
	else if (has_redirections(tokens))
		exec_redirection_cmd(tokens, env, environ, is_tty);
	else
	{
		if (!is_built_in(env, tokens))
			is_execute(env, tokens, environ);
	}
}

void	exec_command(t_list **env, char *line, char **environ, int is_tty)
{
	char	**tokens;

	tokens = tokenize_shell_line(line, *env);
	if (!tokens)
		return ;
	exec_parsed_cmd(tokens, env, environ, is_tty);
	free_mem(tokens);
}
