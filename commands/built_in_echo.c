/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:24:20 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/10 18:29:14 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_commands(t_cmd *cmd, int *i)
{
	while (*i < cmd->argc)
	{
		ft_printf("%s", cmd->args[(*i)]);
		if ((*i) + 1 < cmd->argc)
			ft_printf(" ");
		(*i)++;
	}
}

void	echo_command(t_cmd *cmd)
{
	int		i;
	int		j;
	bool	newline;

	newline = true;
	i = 1;
	while (i < cmd->argc && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		j = 2;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
			break ;
		i++;
		newline = false;
	}
	print_commands(cmd, &i);
	if (newline)
		ft_printf("\n");
	g_signal = 1;
}
