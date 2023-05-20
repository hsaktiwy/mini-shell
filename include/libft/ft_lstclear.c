/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:57:35 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/20 14:23:41 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*next;
	
	if (!(lst))// || !del
		return ;
	node = (*lst);
	while (node != NULL)
	{
		next = node->next;
		if (del)
		{
			del(node->content);
		}
		free(node);
		node = next;
	}
	*lst = NULL;
}
