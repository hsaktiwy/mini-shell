/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_t_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:06:27 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/03 15:06:30 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_lstfree_t_file(t_list **node)
{
	t_file	*file;

	if (*node)
	{
		file = (*node)->content;
		free(file->a_file);
		ft_lstfree_node(node);
	}
}
