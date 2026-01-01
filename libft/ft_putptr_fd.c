/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putptr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 19:59:54 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:00:00 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	char			*alf_hex;
	unsigned long	n;
	int				chars_count;

	chars_count = 0;
	n = (unsigned long)ptr;
	alf_hex = "0123456789abcdef";
	chars_count += write(fd, "0x", 2);
	if (n == 0)
		return (chars_count += write(fd, "0", 1));
	if (n >= 16)
		chars_count += ft_putptr_hex_fd(n / 16, fd);
	chars_count += ft_putchar_fd(alf_hex[n % 16], 1);
	return (chars_count);
}
