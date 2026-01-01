/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putnbr_xxx_fd.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 19:55:59 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:11:26 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_xxx_fd(unsigned int n, int fd)
{
	char	*alf_hex;
	int		chars_count;

	chars_count = 0;
	alf_hex = "0123456789ABCDEF";
	if (n >= 16)
		ft_putnbr_xxx_fd(n / 16, fd);
	ft_putchar_fd(alf_hex[n % 16], 1);
	return (chars_count);
}
