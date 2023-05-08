/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_in_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:41 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/06 18:43:52 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_in_index(t_list **list, t_list *new, int index)
{
	t_list	*previous;
	t_list	*next_n;

	next_n = *list;
	previous = next_n;
	if (ft_lstsize(*list) == index)
	{
		ft_lstadd_back(list, new);
		return ;
	}
	if (index == 0 || !(*list))
	{
		new->next = next_n;
		*list = new;
		return ;
	}
	while (next_n->next && index--)
	{
		previous = next_n;
		next_n = next_n->next;
	}
	previous->next = new;
	if (previous != new)
		new->next = next_n;
}
