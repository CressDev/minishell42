/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 20:00:51 by cress			 #+#	#+#			 */
/*   Updated: 2025/06/24 20:00:54 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

int	ft_printf(char const *fmt, ...)
{
	va_list		arg_ptr;
	int			i;
	int			chars_count;

	i = 0;
	chars_count = 0;
	va_start(arg_ptr, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			chars_count += ft_fmt(arg_ptr, &fmt[i], 1);
		}
		else
		{
			ft_putchar_fd(fmt[i], 1);
			chars_count++;
		}
		i++;
	}
	va_end(arg_ptr);
	return (chars_count);
}
