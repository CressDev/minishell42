/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:02:59 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 13:47:19 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_direct_path(char *command)
{
	char	*command_dup;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			command_dup = ft_strdup(command);
			if (!command_dup)
				return (NULL);
			return (command_dup);
		}
		return (NULL);
	}
	return (NULL);
}

char	*search_in_path_env(char *command, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (free_mem(paths), NULL);
		full_path = ft_strjoin(temp, command);
		if (!full_path)
			return (free(temp), free_mem(paths), NULL);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_mem(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_mem(paths), NULL);
}

char	*find_command_in_path(char *command, t_list *env)
{
	char	*result;
	char	*path_env;
	char	**paths;

	result = check_direct_path(command);
	if (result)
		return (result);
	path_env = get_value(env, "PATH=");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path_env(command, paths));
}

void	create_children(char *full_path, char **tokens, char **environ)
{
	int					status;
	pid_t				pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(full_path, tokens, environ);
		perror("execve failed");
		exit(130);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			rl_replace_line("", 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
	}
	else
		return (perror("fork"), g_signal = 1, (void)0);
}

void	is_execute(t_list **env, char **tokens, char **environ)
{
	char	*full_path;

	if (!tokens[0] || tokens[0][0] == '\0')
	{
		return (write(STDERR_FILENO, ": command not found\n", 20),
			g_signal = 127, (void)0);
	}
	full_path = find_command_in_path(tokens[0], *env);
	if (!full_path)
	{
		if (ft_strchr(tokens[0], '/'))
		{
			write(STDERR_FILENO, tokens[0], ft_strlen(tokens[0]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
		}
		else
		{
			write(STDERR_FILENO, tokens[0], ft_strlen(tokens[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
		}
		return (free(full_path), g_signal = 127, (void)0);
	}
	create_children(full_path, tokens, environ);
	free(full_path);
}
