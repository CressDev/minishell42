/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:30:00 by cress             #+#    #+#             */
/*   Updated: 2025/12/23 11:30:26 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_unquoted_len(char *str, int start, int end)
{
	int		i;
	int		len;
	char	quote;

	i = start;
	len = 0;
	quote = 0;
	while (i < end)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*process_quotes(char *str, int start, int end)
{
	char	*result;
	int		final_len;
	int		i;
	int		j;
	char	quote;

	final_len = calculate_unquoted_len(str, start, end);
	result = malloc(sizeof(char) * (final_len + 1));
	if (!result)
		return (NULL);
	i = start;
	j = 0;
	quote = 0;
	while (i < end)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
