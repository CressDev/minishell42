/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:50 by amonteag          #+#    #+#             */
/*   Updated: 2025/10/02 19:05:12 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && i == 0) || (s[i] != c && s[i - 1] == c))
			len++;
		i++;
	}
	return (len);
}

static char	*ft_get_words(char const *s, char c, int *index)
{
	int		start;
	int		end;
	char	*word;

	start = *index;
	while (s[start] != '\0' && s[start] == c)
		start++;
	end = start;
	while (s[end] != '\0' && s[end] != c)
		end++;
	*index = end;
	word = ft_substr(s, start, end - start);
	return (word);
}

static void	ft_free_mem(char **s, size_t save_words)
{
	size_t	i;

	i = 0;
	while (i < save_words)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	len_words;
	int		index;

	if (!s)
		return (NULL);
	len_words = ft_count_words(s, c);
	str = (char **)malloc((len_words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	index = 0;
	while (i < len_words)
	{
		str[i] = ft_get_words(s, c, &index);
		if (!str[i])
		{
			ft_free_mem(str, i);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
