/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstnew.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cress <cress@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/21 14:04:45 by amonteag		  #+#	#+#			 */
/*   Updated: 2025/07/16 22:08:34 by cress			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content)
{
	t_list	*newnodo;

	newnodo = (t_list *)malloc(sizeof(t_list));
	if (!newnodo)
		return (NULL);
	newnodo->content = (void *)content;
	newnodo->next = NULL;
	newnodo->index = 0;
	return (newnodo);
}
