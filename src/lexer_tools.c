/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/05 16:56:59 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handleCommand(t_list **tokens, char *input, int *index, int *cmd)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	token->type = COMMAND;
	token->value = get_cmd(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
	*cmd = 1;
}

void	handleArg(t_list **tokens, char *input, int *index)
{
	t_token	*cmd;
	t_token	*tmp;
	t_list	*list;
	t_list	*node;

	cmd = NULL;
	list = *tokens;
	while (list)
	{
		tmp = list->content;
		if( tmp->type == COMMAND)
			cmd = tmp;
		list = list->next;
	}
	node = ft_lstnew(get_simple_arg(&input[*index], index));
	ft_lstadd_back(&(((t_cmd *)cmd->value)->arg), node);
}
