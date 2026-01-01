/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:45:00 by cress             #+#    #+#             */
/*   Updated: 2025/12/29 11:20:59 by amonteag         ###   ########.fr       */
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

int	handle_quotes(char c, int *in_single_quote)
{
	if (c == '\'' && !*in_single_quote)
	{
		*in_single_quote = 1;
		return (1);
	}
	else if (c == '\'' && *in_single_quote)
	{
		*in_single_quote = 0;
		return (1);
	}
	return (0);
}

char	*process_char_expan(char *resul, char *raw_token, int *i, t_list *env)
{
	char		*expanded;
	char		*temp;
	static int	in_single_quote = 0;

	if (handle_quotes(raw_token[*i], &in_single_quote))
	{
		temp = ft_strjoin(resul, (char [2]){raw_token[*i], '\0'});
		if (!temp)
			return (free(resul), NULL);
		(*i)++;
		return (free(resul), temp);
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
	(*i)++;
	return (free(resul), temp);
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
