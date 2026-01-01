/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:04:48 by cress             #+#    #+#             */
/*   Updated: 2025/12/25 09:44:47 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_double_operator_token(char operator)
{
	char	*token;

	token = malloc(sizeof(char) * 3);
	if (!token)
		return (NULL);
	token[0] = operator;
	token[1] = operator;
	token[2] = '\0';
	return (token);
}

char	*create_single_operator_token(char operator)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	if (!token)
		return (NULL);
	token[0] = operator;
	token[1] = '\0';
	return (token);
}

int	skip_word_token(char *line, int pos)
{
	char	quote;

	quote = 0;
	while (line[pos] && (quote || (!is_operator(line[pos])
				&& !is_whitespace(line[pos]))))
	{
		if ((line[pos] == '"' || line[pos] == '\'') && !quote)
			quote = line[pos];
		else if (line[pos] == quote)
			quote = 0;
		pos++;
	}
	return (pos);
}

int	count_tokens(char *line, int i)
{
	int	tokens;

	tokens = 0;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		if (is_operator(line[i]))
		{
			tokens++;
			if ((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
				i += 2;
			else
				i++;
		}
		else
		{
			i = skip_word_token(line, i);
			tokens++;
		}
	}
	return (tokens);
}
