/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:57:35 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/20 14:08:52 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*next;
	int		 i = 0;
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
