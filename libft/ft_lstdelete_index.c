/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelete_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:05:27 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 17:22:04 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_node(t_list **node)
{
	if (*node)
	{
		free((*node)->content);
		free((*node));
		*node = NULL;
	}
}

void	ft_lstdelete_index(t_list **list, int index, void (*del)(t_list **))
{
	t_list	*previous;
	t_list	*node;

	if (!(*list))
		return ;
	if (index == 0)
	{
		node = *list;
		*list = (*list)->next;
		del(&node);
		return ;
	}
	node = *list;
	while (node->next && index--)
	{
		previous = node;
		node = node->next;
	}
	previous->next = node->next;
	node->next = NULL;
	del(&node);
}
