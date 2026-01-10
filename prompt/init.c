/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:06:42 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/10 15:06:51 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_list *env)
{
	char	*pwd;
	char	*display_path;
	char	*user_colored;
	char	*path_colored;
	char	*user_name;

	pwd = get_current_pwd(env);
	if (!pwd)
		return (NULL);
	display_path = get_display_path(pwd, get_value(env, "HOME="));
	if (!display_path)
		return (free(pwd), write(1, "Malloc Error\n", 14), NULL);
	user_name = get_value(env, "USER=");
	if (!user_name)
		user_name = "Amonteag";
	user_colored = join_with_color(COLOR_GREEN, user_name, COLOR_RESET);
	path_colored = join_with_color(COLOR_BLUE, display_path, COLOR_RESET);
	if (!user_colored || !path_colored)
		return (free(pwd), free(display_path), free(user_colored),
			free(path_colored), write(1, "Malloc Error\n", 14), NULL);
	user_name = build_prompt_parts(user_colored, path_colored);
	return (free(pwd), free(display_path), free(user_colored),
		free(path_colored), user_name);
}
