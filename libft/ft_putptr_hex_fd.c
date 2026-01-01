/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putptr_hex_fd.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 20:01:37 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:01:39 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_hex_fd(unsigned long n, int fd)
{
	char	*alf_hex;
	int		chars_count;

	chars_count = 0;
	alf_hex = "0123456789abcdef";
	if (n >= 16)
		chars_count += ft_putptr_hex_fd(n / 16, fd);
	chars_count += ft_putchar_fd(alf_hex[n % 16], 1);
	return (chars_count);
}
