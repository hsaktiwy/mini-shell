/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:40:00 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 16:00:59 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_token(t_list	**current, t_g_types g_type)
{
	t_token *token;
	
	if ((*current) == NULL)
		return (0);
	token = (*current)->content;
	if (g_type == REDIRECTION)
	{
		if(token->type == IN_REDIRECT || token->type == OUT_REDIRECT
			|| token->type == APPEND_REDIRECT || token->type == HERE_DOC)
			return (1);
	}else if (g_type == CMD)
	{
		if (token->type == COMMAND)
			return (1);
	}else if (g_type == G_PIPE)
	{
		if (token->type == PIPE)
			return (1);
	}
	return (0);
}

t_ast	*create_ast_node(t_list	**current, t_g_types type)
{
	t_ast	*node;

	node = ast_new_node();
	if (!node && (*current) == NULL)
		return (NULL);
	printf("This in \n");
	printf("in prasing %s\n", ((t_cmd *)(((t_token *)((*current)->content))->value))->cmd);
	node->content = (*current)->content;
	node->type = type;
	(*current) = (*current)->next;
	return (node);
}

t_ast	*simple_command(t_list	**current)
{
	t_ast	*redirection;
	t_ast	*cmd;
	t_ast	*node;

	
	if ((*current) == NULL)
		return (NULL);
	if (check_token(current, REDIRECTION))
		redirection = create_ast_node(current, REDIRECTION);
	else
		redirection = NULL;
	if (check_token(current, CMD))
		cmd = create_ast_node(current, CMD);
	else
		cmd = NULL;
	if (redirection == NULL && check_token(current, REDIRECTION))
		redirection = create_ast_node(current, REDIRECTION);
	node = ast_new_node();
	ast_set_data(node, S_COMMAND, NULL);
	ast_add_l_r(node, cmd, redirection);
	return (node);
}

t_ast	*pipeline(t_list **current)
{
	t_ast	*p_command;
	t_ast	*p_pipeline;

	p_pipeline = NULL;
	if ((*current) != NULL)
	{
		if (check_token(current, G_PIPE))
		{
			(*current) = (*current)->next;
			p_command = command(current);
			if (!p_command)
				return (NULL);
			p_pipeline = ast_new_node();
			ast_set_data(p_pipeline, PIPELINE, NULL);
			ast_add_l_r(p_pipeline, p_command, NULL);	
		}
	}
	return (p_pipeline);
}

t_ast	*command(t_list **current)
{
	t_ast	*tree;
	t_ast	*simple_cmd;
	t_ast	*c_pipeline;
	
	tree = NULL;
	if ((*current) != NULL)
	{
		simple_cmd = simple_command(current);
		if (simple_cmd == NULL)
			return (NULL);
		c_pipeline = pipeline(current);
		tree = ast_new_node();
		ast_set_data(tree, G_COMMAND, NULL);
		ast_add_l_r(tree, simple_cmd, c_pipeline);	
	}
	return (tree);
}
