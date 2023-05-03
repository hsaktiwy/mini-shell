/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:39 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/01 16:24:43 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// int		lexer(t_list **tokens, char *input)
// {
// 	int		i;
// 	t_token *token;
// 	//char	*data;

// 	i = 0;	
// 	token = NULL;
// 	while (input[i])
// 	{
// 		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
// 		{
// 			// arg is a EOF
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			i = i + 2;
// 			token->type = HERE_DOC;
// 			token->value = get_file(&input[i], &i);
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 		}else if (input[i] == '<' && input[i + 1] && input[i + 1] != '<')
// 		{
// 			// arg is a FILE
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			++i;
// 			token->type = IN_REDIRECT;
// 			token->value = get_file(&input[i], &i);
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 		}
// 		else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
// 		{
// 			// arg is a EOF
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			i = i + 2;
// 			token->type = APPEND_REDIRECT;
// 			token->value = get_file(&input[i], &i);
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 		}else if (input[i] == '>' && input[i + 1] && input[i + 1] != '>')
// 		{
// 			// arg is a FILE
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			++i;
// 			token->type = OUT_REDIRECT;
// 			token->value = get_file(&input[i], &i);
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 		}else if (input[i] == '|')
// 		{
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			token->type = PIPE;
// 			token->value = NULL;
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 			i++;
// 		}else{
// 			token = (t_token *)malloc(sizeof(t_token));
// 			if (!token)
// 				return (1);
// 			token->type = COMMAND;
// 			token->value =	get_cmd(&input[i], &i);
// 			ft_lstadd_back(tokens,ft_lstnew(token));
// 		}
// 		if (iswhitespace(input[i]))
// 			i++;
// 	}
// 	return (0);
// }
void handleHereDoc(t_list **tokens, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	*index += 2;
	token->type = HERE_DOC;
	token->value = get_file(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handleInRedirect(t_list **tokens, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	++(*index);
	token->type = IN_REDIRECT;
	token->value = get_file(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handleAppendRedirect(t_list **tokens, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	*index += 2;
	token->type = APPEND_REDIRECT;
	token->value = get_file(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handleOutRedirect(t_list **tokens, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	++(*index);
	token->type = OUT_REDIRECT;
	token->value = get_file(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handlePipe(t_list **tokens, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	token->type = PIPE;
	token->value = NULL;
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*index)++;
}

void handleCommand(t_list **tokens, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	token->type = COMMAND;
	token->value = get_cmd(&input[*index], index);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

int lexer(t_list **tokens, char *input)
{
	int i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
			handleHereDoc(tokens, input, &i);
		else if (input[i] == '<' && input[i + 1] && input[i + 1] != '<')
			handleInRedirect(tokens, input, &i);
		else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
			handleAppendRedirect(tokens, input, &i);
		else if (input[i] == '>' && input[i + 1] && input[i + 1] != '>')
			handleOutRedirect(tokens, input, &i);
		else if (input[i] == '|')
			handlePipe(tokens, &i);
		else
			handleCommand(tokens, input, &i);
		
		if (iswhitespace(input[i]))
			i++;
	}
	return 0;
}
