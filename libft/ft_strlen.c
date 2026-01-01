/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlen.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: amonteag <amonteag@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:07:58 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/04/21 14:08:00 by amonteag		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0 ;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}
