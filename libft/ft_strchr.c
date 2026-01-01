/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: amonteag <amonteag@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:06:57 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/04/21 14:07:00 by amonteag		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	chr;

	chr = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == chr)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
