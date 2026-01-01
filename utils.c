/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 08:55:03 by cress             #+#    #+#             */
/*   Updated: 2025/12/24 08:55:41 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	skip_spaces(char *line, int pos)
{
	while (line[pos] && is_whitespace(line[pos]))
		pos++;
	return (pos);
}
