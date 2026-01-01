/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:07:27 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/06/28 21:52:03 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*a;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	i = ft_strlen(s2) + ft_strlen(s1) + 1;
	if (i == 0)
		return (NULL);
	a = malloc(sizeof(char) * i);
	if (!a)
		return (NULL);
	ft_strlcpy(a, s1, i);
	ft_strlcat(a, s2, i);
	return (a);
}
