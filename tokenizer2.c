/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 09:43:35 by cress             #+#    #+#             */
/*   Updated: 2025/12/30 09:51:17 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <ctype.h>

static int	is_cross_operator(char *line, int pos, char op)
{
	int	i;

	i = pos + 1;
	while (line[i] && isspace((unsigned char)line[i]))
		i++;
	if ((op == '<' && line[i] == '>') || (op == '>' && line[i] == '<'))
		return (1);
	return (0);
}

char	*extract_left_operator_token(char *line, int pos)
{
	int	i;
	int	count;
	int	j;

	i = pos + 1;
	count = 1;
	while (line[i] == '<')
	{
		count++;
		i++;
	}
	if (count > 2)
		return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
	if (is_cross_operator(line, pos, '<'))
		return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
	if (count == 2)
	{
		j = i;
		while (line[j] == ' ')
			j++;
		if (line[j] == '>' || line[j] == '<')
			return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
		return (create_double_operator_token('<'));
	}
	return (create_single_operator_token('<'));
}

char	*extract_right_operator_token(char *line, int pos)
{
	int	i;
	int	count;
	int	j;

	i = pos + 1;
	count = 1;
	while (line[i] == '>')
	{
		count++;
		i++;
	}
	if (count > 2)
		return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
	if (is_cross_operator(line, pos, '>'))
		return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
	if (count == 2)
	{
		j = i;
		while (line[j] == ' ')
			j++;
		if (line[j] == '<' || line[j] == '>')
			return (write(2, "syntax error\n", 14), g_signal = 2, NULL);
		return (create_double_operator_token('>'));
	}
	return (create_single_operator_token('>'));
}

char	*extract_operator_token(char *line, int pos)
{
	if (line[pos] == '<')
		return (extract_left_operator_token(line, pos));
	else if (line[pos] == '>')
		return (extract_right_operator_token(line, pos));
	else
		return (create_single_operator_token(line[pos]));
}
