/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_fmt.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 19:55:00 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:05:45 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_fmt(va_list arg_ptr, char const *fmt, int i)
{
	int	chars_count;

	chars_count = 0;
	if (*fmt == 'c')
		chars_count += ft_putchar_fd(va_arg(arg_ptr, int), i);
	if (*fmt == 's')
		chars_count += ft_putstr_fd(va_arg(arg_ptr, char *), i);
	if (*fmt == 'd')
		chars_count += ft_putnbr_fd(va_arg(arg_ptr, int), i);
	if (*fmt == 'i')
		chars_count += ft_putnbr_fd(va_arg(arg_ptr, int), i);
	if (*fmt == 'p')
		chars_count += ft_putptr_fd(va_arg(arg_ptr, void *), i);
	if (*fmt == 'u')
		chars_count += ft_putunsig_fd(va_arg(arg_ptr, int), i);
	if (*fmt == 'x')
		chars_count += ft_putnbr_hex_fd(va_arg(arg_ptr, int), i);
	if (*fmt == 'X')
		chars_count += ft_putnbr_xxx_fd(va_arg(arg_ptr, int), i);
	if (*fmt == '%')
		chars_count += ft_putchar_fd('%', i);
	return (chars_count);
}
