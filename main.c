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

int	main(int ac, char **av, char **environ)
{
	t_list	*env;
	t_cmd	*cmd;

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
	cmd = init_cmd(environ);
	read_line(cmd);
	ft_lstclear(&env, free);
}
