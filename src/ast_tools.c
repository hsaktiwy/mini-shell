/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:58:50 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/04/30 19:07:30 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_ast   *ast_new_node()
{
	t_ast   *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->content = NULL;
	node->type = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void    ast_add_l_r(t_ast *node, t_ast *n_left, t_ast *n_right)
{
	if (!node)
		return ;
	node->left  = n_left;
	node->right = n_right;
}

void    ast_set_data(t_ast *node, t_g_types type, void *content)
{
	if (!node)
		return ;
	node->type = type;
	node->content = content;
}
