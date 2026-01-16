/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:45:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/16 11:14:25 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(char *raw_token, int *pos, t_list *env)
{
	int		start;
	int		end;
	char	*result;

	result = handle_special_vars(raw_token, pos);
	if (result)
		return (result);
	start = *pos + 1;
	end = start;
	while (raw_token[end] && (unsigned char)raw_token[end] <= 127
		&& (ft_isalnum(raw_token[end]) || raw_token[end] == '_'))
		end++;
	if (end == start)
	{
		*pos = start;
		result = ft_strdup("$");
		if (!result)
			write(2, "Error: malloc failed for dollar sign\n", 38);
		return (result);
	}
	*pos = end;
	return (extract_var_value(raw_token, start, end, env));
}

static char	*join_and_free(char *res, char *var)
{
	char	*new;

	if (!res || !var)
		return (free(res), free(var), NULL);
	new = ft_strjoin(res, var);
	free(res);
	free(var);
	return (new);
}

static char *join_char(char *res, char c)
{
	char	*new;
	size_t	len;
	size_t	i;

	if (!res)
		return (NULL);
	len = ft_strlen(res);
	new = malloc(len + 2);
	if (!new)
		return (free(res), NULL);
	i = 0;
	while (i < len)
	{
		new[i] = res[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(res);
	return (new);
}

static char	*expand_string(char *content, t_list **env)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
			res = join_and_free(res, expand_variable(content, &i, *env));
		else
			res = join_char(res, content[i++]);
	}
	return (res);
}

void	expand_token(t_token *token, t_envs *envs)
{
	char	*new;

	if (token->quote == 1)
		return ;
	new = expand_string(token->content, envs->env);
	if (!new)
		return ;
	free(token->content);
	token->content = new;
}
