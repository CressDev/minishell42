/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putunsig_fd.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 20:01:09 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:01:11 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsig_fd(unsigned int n, int fd)
{
	char	digit;
	int		chars_count;

	chars_count = 0;
	if (n >= 10)
		chars_count += ft_putunsig_fd(n / 10, fd);
	digit = (n % 10) + '0';
	chars_count += write(fd, &digit, 1);
	return (chars_count);
}
