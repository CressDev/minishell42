/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:04:20 by cress             #+#    #+#             */
/*   Updated: 2026/01/13 20:12:45 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_command(t_cmd *cmd)
{
	int	exit_code;
	int	arg_count;

	arg_count = ft_count(cmd->args);
	if (arg_count == 1)
		exit_code = g_signal;
	else if (arg_count == 2)
	{
		if (is_valid_number(cmd->args[1]))
			exit_code = ft_atoi(cmd->args[1]);
		else
		{
			write(STDERR_FILENO, "exit: ", 7);
			write(STDERR_FILENO, cmd->args[1], ft_strlen(cmd->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit(2);
		}
	}
	else
		return (write(2, "exit: too many arguments\n", 25), g_signal = 1,
			(void)0);
	exit(exit_code);
}
