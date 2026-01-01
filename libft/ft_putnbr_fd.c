/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putnbr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/19 11:32:03 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/05/03 21:09:17 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	int		chars_count;

	chars_count = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		chars_count += write(fd, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
		chars_count += ft_putnbr_fd(n / 10, fd);
	digit = (n % 10) + '0';
	chars_count += write(fd, &digit, 1);
	return (chars_count);
}
