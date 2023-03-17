/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:39 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 10:30:53 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		lexer(t_list **tokens, char *input)
{
	int		i;
	t_token *token;
	//char	*data;

	i = 0;	
	token = NULL;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
		{
			// arg is a EOF
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			i = i + 2;
			token->type = HERE_DOC;
			token->value = next_arg(&input[i], &i);
			ft_lstadd_back(tokens,ft_lstnew(token));
		}else if (input[i] == '<' && input[i + 1] && input[i + 1] != '<')
		{
			// arg is a FILE
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			++i;
			token->type = IN_REDIRECT;
			token->value = next_arg(&input[i], &i);
			ft_lstadd_back(tokens,ft_lstnew(token));
		}
		if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
		{
			// arg is a EOF
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			i = i + 2;
			token->type = APPEND_REDIRECT;
			token->value = next_arg(&input[i], &i);
			ft_lstadd_back(tokens,ft_lstnew(token));
		}else if (input[i] == '>' && input[i + 1] && input[i + 1] != '>')
		{
			// arg is a FILE
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			++i;
			token->type = OUT_REDIRECT;
			token->value = next_arg(&input[i], &i);
			ft_lstadd_back(tokens,ft_lstnew(token));
		}else if (input[i] == '|')
		{
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			token->type = PIPE;
			token->value = NULL;
			ft_lstadd_back(tokens,ft_lstnew(token));
		}else{
			token = (t_token *)malloc(sizeof(t_token));
			if (!token)
				return (1);
			token->type = COMMAND;
			//token->value =	get_cmd(&input[i], &i);
			ft_lstadd_back(tokens,ft_lstnew(token));
		}
	}
	return (0);
}
