/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memset.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: amonteag <amonteag@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:06:06 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/04/21 14:06:08 by amonteag		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	value;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	value = (unsigned char)c;
	while (i < n)
	{
		str[i] = value;
		i++;
	}
	return (s);
}
