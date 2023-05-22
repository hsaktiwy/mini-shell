/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/22 15:26:49 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handleCommand(t_list **tokens, t_env *env,char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return 0;
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

void	handleArg(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*cmd;
	t_token	*tmp;
	t_list	*list;
	t_list	*node;
	char	*file;

	cmd = NULL;
	node = NULL;
	list = *tokens;
	while (list)
	{
		tmp = list->content;
		if( tmp->type == COMMAND)
			cmd = tmp;
		list = list->next;
	}
	if (input[*index] == '$' && is_splitable_env(&input[*index]))
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

void	ini_count(t_token **token)
{
	t_cmd	*cmd;
	t_list	*current;
	t_file	*arg;

	cmd = (*token)->value;
	cmd->arg_count = 0;
	current = cmd->arg;

	while (current)
	{
		arg = current->content;
		if (arg->a_file)
			cmd->arg_count++;
		current = current->next;
	}
}

void	ini_arg_count(t_list **tokens)
{
	t_list	*current;
	t_token	*token;

	current = *tokens;
	while (current)
	{
		token = current->content;
		if (token->type == COMMAND)
			ini_count(&token);
		current = current->next;
	}
}
int	lexical_erreur(char	*input)
{
	int		i;
	char	c;
	int		c_i;

	i = -1;
	c = '\0';
	c_i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' && c == '\0')
		{
			c = '\"';
			c_i = i;
		}
		else if (input[i] == '\'' && c == '\0')
		{
			c = '\'';
			c_i = i;
		}
		else if ((input[i] == '\'' && c == '\'') || (input[i] == '\"' && c == '\"'))
			c = '\0';
		if (input[i] != '\0' && !ft_isprint(input[i]))
			return (i);
	}
	if (c == '\'' || c == '\"')
		return (c_i);
	return (-1);
}


