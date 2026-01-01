/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:44:18 by cress             #+#    #+#             */
/*   Updated: 2025/12/25 10:06:55 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_list *lst, char *str)
{
	int	size;

	size = ft_strlen(str);
	if (!lst || !str)
		return (NULL);
	while (ft_strncmp(lst->content, str, size) != 0 && lst->next != NULL)
		lst = lst->next;
	if (ft_strncmp(lst->content, str, size) == 0)
		return (lst->content + size);
	return (NULL);
}

char	*get_display_path(char *pwd, char *home)
{
	char	*new_pwd;

	if (home && ft_strcmp(pwd, home) == 0)
	{
		new_pwd = ft_strdup("~");
		if (!new_pwd)
			return (NULL);
		return (new_pwd);
	}
	else
	{
		new_pwd = ft_strdup(pwd);
		if (!new_pwd)
			return (NULL);
		return (new_pwd);
	}
}

char	*join_with_color(char *color, char *text, char *reset)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(color, text);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, reset);
	if (!result)
		return (free(temp), NULL);
	free(temp);
	return (result);
}

char	*build_prompt_parts(char *user_colored, char *path_colored)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(user_colored, ":");
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, path_colored);
	if (!temp2)
		return (free(temp1), NULL);
	free(temp1);
	result = ft_strjoin(temp2, "$ ");
	if (!result)
		return (free(temp2), NULL);
	free(temp2);
	return (result);
}

char	*get_current_pwd(t_list *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_value(env, "PWD=");
		if (!pwd)
			pwd = "/";
		pwd = ft_strdup(pwd);
		if (!pwd)
		{
			write(1, "Malloc Error\n", 14);
			return (NULL);
		}
	}
	return (pwd);
}
