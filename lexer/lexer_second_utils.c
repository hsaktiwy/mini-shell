/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_second_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:14:11 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 18:18:25 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	lexical_errur_helper(char input, char *c, int *c_i, int i)
{
	if (input == '\"' && *c == '\0')
	{
		*c = '\"';
		*c_i = i;
	}
	else if (input == '\'' && *c == '\0')
	{
		*c = '\'';
		*c_i = i;
	}
	else if ((input == '\'' && *c == '\'') || (input == '\"' && *c == '\"'))
		*c = '\0';
}

int	parser_erreur(char	*input)
{
	int		i;
	char	c;
	int		c_i;

	i = -1;
	c = '\0';
	c_i = -1;
	while (input[++i])
		lexical_errur_helper(input[i], &c, &c_i, i);
	if (c)
		return (c_i);
	return (-1);
}
