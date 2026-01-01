/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:00:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/01 10:11:13 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_token(char *line, int *pos, t_list *env)
{
	int		start;
	int		end;
	char	*raw_token;
	char	*expanded;
	char	*result;

	start = *pos;
	if (is_operator(line[*pos]))
	{
		raw_token = extract_operator_token(line, *pos);
		if (!raw_token)
			return (NULL);
		if (ft_strlen(raw_token) == 2)
			*pos += 2;
		else
			*pos += 1;
		return (raw_token);
	}
	end = skip_word_token(line, *pos);
	*pos = end;
	raw_token = ft_substr(line, start, end - start);
	expanded = process_expansions(raw_token, env);
	result = process_quotes(expanded, 0, ft_strlen(expanded));
	return (free(raw_token), free(expanded), result);
}

static char	*get_heredoc_token(char *line, int *pos)
{
	int		start;
	int		end;
	char	*raw_token;
	char	*result;

	start = *pos;
	end = skip_word_token(line, *pos);
	raw_token = ft_substr(line, start, end - start);
	result = process_quotes(raw_token, 0, ft_strlen(raw_token));
	free(raw_token);
	*pos = end;
	return (result);
}

static int	fill_tokens_array(char **tokens, int num_tokens,
						char *line, t_list *env)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < num_tokens)
	{
		pos = skip_spaces((char *)line, pos);
		if (i > 0 && ft_strcmp(tokens[i - 1], "<<") == 0)
			tokens[i] = get_heredoc_token(line, &pos);
		else
			tokens[i] = extract_token(line, &pos, env);
		if (!tokens[i])
			return (0);
		i++;
	}
	tokens[i] = NULL;
	return (1);
}

char	**tokenize_shell_line(char *line, t_list *env)
{
	char	**tokens;
	int		num_tokens;

	num_tokens = count_tokens(line, 0);
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (!tokens)
		return (NULL);
	if (!fill_tokens_array(tokens, num_tokens, line, env))
		return (free_mem(tokens), NULL);
	return (tokens);
}
