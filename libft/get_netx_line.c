/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_netx_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/07/29 22:32:08 by cress			 #+#	#+#			 */
/*   Updated: 2025/08/06 21:50:55 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_next_line(char *static_char)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*next_line;

	i = 0;
	if (!static_char)
		return (NULL);
	while (static_char[i] && static_char[i] != '\n')
		i++;
	if (static_char[i] == '\0')
		return (NULL);
	i++;
	if (static_char[i] == '\0')
		return (NULL);
	len = ft_strlen(static_char) - i;
	next_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!next_line)
		return (NULL);
	j = 0;
	while (static_char[i] != '\0')
		next_line[j++] = static_char[i++];
	next_line[j] = '\0';
	return (next_line);
}

char	*ft_get_line(char *static_char)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	if (!static_char || static_char[0] == '\0')
		return (NULL);
	while (static_char[i] && static_char[i] != '\n')
		i++;
	if (static_char[i] == '\n')
		new_line = malloc(sizeof(char) * (i + 2));
	else
		new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_line[j] = static_char[j];
		j++;
	}
	if (static_char[j] == '\n')
		new_line[j++] = '\0';
	new_line[j] = '\0';
	return (new_line);
}

char	*ft_read_line(int fd, char *static_char)
{
	int		bytes;
	char	*new_str;
	char	*aux;

	bytes = 1;
	new_str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_str || fd < 0)
		return (NULL);
	while (!ft_strchr(static_char, '\n') && bytes > 0)
	{
		bytes = read(fd, new_str, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(new_str);
			free(static_char);
			return (NULL);
		}
		new_str[bytes] = '\0';
		aux = static_char;
		static_char = ft_strjoin(static_char, new_str);
		if (aux && aux != static_char)
			free(aux);
	}
	free(new_str);
	return (static_char);
}

char	*init_static(char *static_char)
{
	static_char = malloc(1);
	if (!static_char)
		return (NULL);
	static_char[0] = '\0';
	return (static_char);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*static_char;
	char		*old_static;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!static_char)
		static_char = init_static(static_char);
	static_char = ft_read_line(fd, static_char);
	if (!static_char)
		return (NULL);
	new_line = ft_get_line(static_char);
	if (!new_line)
	{
		free(static_char);
		static_char = NULL;
		return (NULL);
	}
	old_static = static_char;
	static_char = ft_next_line(static_char);
	if (old_static != static_char)
		free(old_static);
	return (new_line);
}
