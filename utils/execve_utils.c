/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:02:59 by cress             #+#    #+#             */
/*   Updated: 2026/01/12 20:31:37 by kjroydev         ###   ########.fr       */
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
