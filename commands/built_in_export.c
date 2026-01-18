 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:19:30 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 11:47:00 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	export_handle_arg(t_cmd *cmd, char *arg)
{
	int		j;
	char	*eq;

	eq = NULL;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '=')
		{
			eq = (char *)&arg[j];
			break;
		}
		j++;
	}
	
	if (!is_valid_identifier(arg))
	{
		ft_printf("minishell: export: %s: not a valid identifier\n", arg);
		g_signal = 1;
	}
	else if (eq)
	{
		if (!handler_var(cmd->envs->env, arg, 0))
		add_new_var(cmd->envs->env, arg);
	}
}

static void	export_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->argc)
	{
		export_handle_arg(cmd, cmd->args[i]);
		i++;
	}
}

void	export_command(t_cmd *cmd)
{
	t_list	*current;

	g_signal = 0;
	if (cmd->argc == 1)
	{
		current = *cmd->envs->env;
		order_env(current);
		while(current)
		{
			ft_printf("declare -x %s\n", current->content);
			current = current->next;
		}
	}
	else
	{
		export_args(cmd);
	}
}

