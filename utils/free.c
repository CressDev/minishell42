/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:26:07 by cress             #+#    #+#             */
/*   Updated: 2026/01/15 20:56:16 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_env(t_list **env)
{
	t_list	*current;
	t_list	*tmp;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = tmp;
	}
	*env = NULL;
}

void	free_cmd_start(t_cmd **cmd)
{
	t_cmd	*next;

	if (!cmd || !*cmd)
		return ;
	next = (*cmd)->next;
	if ((*cmd)->args)
		free_mem((*cmd)->args);
	if ((*cmd)->heredoc_delimiter)
		free_mem((*cmd)->heredoc_delimiter);
	if ((*cmd)->input_file)
		free((*cmd)->input_file);
	if ((*cmd)->output_file)
		free((*cmd)->output_file);
	free(*cmd);
	*cmd = NULL;
	if (next)
		free_cmd_start(&next);
}

void	destroy_fsm(t_fsm **fsm)
{
	if (!fsm || !*fsm)
		return ;
	free((*fsm)->input);
	free((*fsm)->token);
	(*fsm)->input = NULL;
	(*fsm)->token = NULL;
	free(*fsm);
	*fsm = NULL;
}
