/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/31 14:16:20 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_list **tokens, int *index, int *cmd)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	add_fake_cmd(tokens, *cmd);
	token->type = PIPE;
	token->value = NULL;
	g_pipe_count(g_pipe_count(-1) + 1);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*index)++;
	*cmd = 0;
}

// this int return  is weird need to get more check ?
int	handle_command(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = COMMAND;
	token->value = get_cmd(env, &input[*index], index);
	if (token->value)
	{
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (1);
	}
	else
		free(token);
	return (0);
}

void	handle_arg(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*cmd;
	t_list	*node;
	char	*file;

	cmd = NULL;
	node = NULL;
	cmd = last_cmd(tokens);
	if (is_splitable_env(&input[*index]))
	{
		file = get_simple_arg(env, &input[*index], index);
		if (file)
			node = ft_lstnew(creat_arg(file, VARIABLE));
	}
	else
	{
		file = get_simple_arg(env, &input[*index], index);
		if (file)
			node = ft_lstnew(creat_arg(file, WORD));
	}
	if (node)
		ft_lstadd_back(&(((t_cmd *)cmd->value)->arg), node);
}
