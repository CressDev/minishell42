/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:24:20 by kjroydev          #+#    #+#             */
/*   Updated: 2026/01/18 13:42:28 by kjroydev         ###   ########.fr       */
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
	g_signal = 0;
	return (0);
}

void	echo_command(t_cmd *cmd)
{
	int		i;
	int		j;
	bool	newline;

	newline = true;
	i = 1;
	while (i < cmd->argc)
	{
		if (cmd->args[i][0] == '-')
		{
			j = 1;
			while (cmd->args[i][j] == 'n')
				j++;
			if (j > 1 && cmd->args[i][j] == '\0')
			{
				newline = false;
				i++;
				continue ;
			}
		}
		break ;
	}
	print_commands(cmd, &i);
	if (newline)
		ft_printf("\n");
}
