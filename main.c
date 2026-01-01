/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:24:05 by cress             #+#    #+#             */
/*   Updated: 2025/08/20 10:24:33 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	show_init_ms(void)
{
	ft_printf("\033[95m%s\033[0m", "\n\
		███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
		████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
		██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
		██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
		██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
		\n	\n");
}

static t_list	*init_env(char **environ)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	if (!environ || !environ[0])
		return (env = ft_lstnew(ft_strdup("SHLVL=1")));
	env = ft_lstnew(ft_strdup(environ[0]));
	if (!env)
		return (NULL);
	if (!(env->content) && env)
		free(env);
	while (environ[++i])
	{
		new = ft_lstnew(ft_strdup(environ[i]));
		if (!(new->content) && new)
			free(new);
		if (!new)
			return (ft_lstclear(&env, free), NULL);
		ft_lstadd_back(&env, new);
	}
	return (env);
}

int	main(int ac, char **av, char **environ)
{
	t_list	*env;

	(void)av;
	if (ac > 1)
		return (1);
	if (isatty(STDIN_FILENO))
		show_init_ms();
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(environ);
	if (env == NULL)
		return (write(1, "Error\n", 6));
	read_line(env, environ);
	ft_lstclear(&env, free);
}
