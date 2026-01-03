/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:45:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/03 08:33:27 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *raw_token, int *pos, t_list *env)
{
	int		start;
	int		end;
	char	*resul;

	resul = handle_special_vars(raw_token, pos);
	if (resul)
		return (resul);
	start = *pos + 1;
	end = start;
	while (raw_token[end] && (unsigned char)raw_token[end] <= 127
		&& (ft_isalnum(raw_token[end]) || raw_token[end] == '_'))
		end++;
	if (end == start)
	{
		*pos = start;
		resul = ft_strdup("$");
		if (!resul)
			write(2, "Error: malloc failed for dollar sign\n", 38);
		return (resul);
	}
	*pos = end;
	return (extract_var_value(raw_token, start, end, env));
}

char	*append_expansion(char *resul, char *expanded)
{
	char	*temp;

	if (!resul || !expanded)
		return (NULL);
	temp = ft_strjoin(resul, expanded);
	if (!temp)
		return (NULL);
	free(resul);
	free(expanded);
	return (temp);
}

void get_quote_context(const char *raw_token, int upto, 
					int *in_single_quote, int *in_double_quote)
{
	int	j;

	j = 0;
	*in_single_quote = 0;
	*in_double_quote = 0;
	while (j < upto) {
		if (raw_token[j] == '\'' && !(*in_double_quote))
			*in_single_quote = !(*in_single_quote);
		else if (raw_token[j] == '"' && !(*in_single_quote))
			*in_double_quote = !(*in_double_quote);
		j++;
	}
}

char *process_char_expan(char *resul, char *raw_token, int *i, t_list *env)
{
	char	*expanded;
	char	*temp;
	int		in_single_quote;
	int		in_double_quote;
	
	get_quote_context(raw_token, *i, &in_single_quote, &in_double_quote);
	if (raw_token[*i] == '\'' && !in_double_quote)
	{
		temp = ft_strjoin(resul, (char [2]){raw_token[*i], '\0'});
		if (!temp)
			return (free(resul), NULL);
		return ((*i)++, free(resul), temp);
	}
	if (raw_token[*i] == '$' && !in_single_quote)
	{
		expanded = expand_variable(raw_token, i, env);
		if (!expanded)
			return (free(resul), NULL);
		resul = append_expansion(resul, expanded);
		return (resul);
	}
	temp = ft_strjoin(resul, (char [2]){raw_token[*i], '\0'});
	if (!temp)
		return (free(resul), NULL);
	return ((*i)++, free(resul), temp);
}

char	*process_expansions(char *raw_token, t_list *env)
{
	char	*resul;
	int		i;

	if (!raw_token)
		return (NULL);
	resul = ft_strdup("");
	if (!resul)
		return (NULL);
	i = 0;
	while (raw_token[i])
	{
		resul = process_char_expan(resul, raw_token, &i, env);
		if (!resul)
			return (NULL);
	}
	return (resul);
}