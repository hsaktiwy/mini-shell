/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:47:37 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/15 17:01:24 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*next;
	int		res;

	res = 0;
	if (!lst)
		return (0);
	next = lst;
	res++;
	while (next->next != NULL)
	{
		next = next->next;
		res++;
	}
	return (res);
}
