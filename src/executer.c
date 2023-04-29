/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:11 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 10:31:13 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	display_tokens(t_list	*tokens)
{
	t_list	*list;

	list = tokens;
	printf("Displaying a tokens (list) : \n");
	while (list)
	{
		t_token *token;

		token = list->content;
		if (token->type == IN_REDIRECT)
		{
			printf("	type : <\n");
			printf("		Data : %s\n", ((t_file *)token->value)->a_file);
		}
		if (token->type == OUT_REDIRECT)
		{
			printf("	type : >\n");
			printf("		Data : %s\n", ((t_file *)token->value)->a_file);
		}
		if (token->type == HERE_DOC)
		{
			printf("	type : <<\n");
			printf("		Data : %s\n", ((t_file *)token->value)->a_file);
		}
		if (token->type == APPEND_REDIRECT)
		{
			printf("	type : >>\n");
			printf("		Data : %s\n", ((t_file *)token->value)->a_file);
		}
		if (token->type == PIPE)
		{
			printf("	type : |\n");
			printf("		Data : %p\n", token->value);
		}
		if (token->type == COMMAND)
		{
			printf("	type : COMMOND\n");
			printf("		CMD : %s\n", ((t_cmd *)token->value)->cmd);
			t_list 	*arg = ((t_cmd *)token->value)->arg;
			printf("		Data :");
			while (arg)
			{
				printf("	%s",(char *)arg->content);
				arg = arg->next;
			}
			printf("\n");
		}
		list = list->next;
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

void	executer(char *input)
{
	t_list	*tokens;
	int		err_lex;
	
	tokens = NULL;
	// lexer erreur traitement'
	err_lex = lexical_erreur(input);
	if (err_lex != -1)
		lexer_err(&input[err_lex]);
	else
		lexer(&tokens, input);
	if (err_lex == -1)
		display_tokens(tokens);
	// free tokens next;
	free_tokens(&tokens);
}