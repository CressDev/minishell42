/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: amonteag <amonteag@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:05:54 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/04/21 14:05:56 by amonteag		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*orig;

	if (n == 0 || dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	orig = (const unsigned char *)src;
	if (dst < orig)
		ft_memcpy(dst, orig, n);
	else
	{
		while (n > 0)
		{
			n--;
			dst[n] = orig[n];
		}
	}
	return (dest);
}
