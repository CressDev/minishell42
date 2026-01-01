/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:25:00 by cress             #+#    #+#             */
/*   Updated: 2025/12/23 12:47:03 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name_with_eq(char *raw_token, int start, int end)
{
	char	*var_name;
	char	*var_name_eq;

	var_name = ft_substr(raw_token, start, end - start);
	if (!var_name)
		return (NULL);
	var_name_eq = ft_strjoin(var_name, "=");
	free(var_name);
	if (!var_name_eq)
		return (NULL);
	return (var_name_eq);
}

char	*handle_special_vars(char *raw_token, int *pos)
{
	char	*result;

	if (raw_token[*pos + 1] == '?')
	{
		*pos = *pos + 2;
		result = ft_itoa(g_signal);
		if (!result)
		{
			write(2, "Error: malloc failed for exit code\n", 36);
			return (NULL);
		}
		return (result);
	}
	if (raw_token[*pos + 1] == '-')
	{
		*pos = *pos + 2;
		result = ft_strdup("himBHs");
		if (!result)
			return (write(2, "Error: malloc failed for shell flags\n", 38),
				NULL);
		return (result);
	}
	return (NULL);
}

char	*extract_var_value(char *raw_token, int start, int end, t_list *env)
{
	char	*var_name_eq;
	char	*var_value;
	char	*result;

	var_name_eq = get_var_name_with_eq(raw_token, start, end);
	if (!var_name_eq)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty string\n", 39);
		return (result);
	}
	var_value = get_value(env, var_name_eq);
	free(var_name_eq);
	if (!var_value)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty var\n", 36);
		return (result);
	}
	result = ft_strdup(var_value);
	if (!result)
		write(2, "Error: malloc failed for var value\n", 36);
	return (result);
}
