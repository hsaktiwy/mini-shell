/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:48:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/03 18:14:08 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int good_piping(char *input, int *i)
{
	int	c;

	c = 0;
	while (input[c + *i] && ft_isprint(input[c + *i]) && input[c + *i] != '|')
		c++;
	if (input[c + *i] == '|' && c == 0)
		return (*i += c,0);
	return (*i += c ,1);
}

int printf_error(int boolean)
{
	if (boolean == 0)
	{
		printf("mini-shell:	syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

void	printf_error_redi(t_token *token, t_list *list)
{
	if ((token->type == IN_REDIRECT || token->type == HERE_DOC) && list)
		printf("mini-shell:	syntax error near unexpected token `<'\n");
	else if (token->type == OUT_REDIRECT && list)
		printf("mini-shell:	syntax error near unexpected token `>'\n");
	else if (token->type == APPEND_REDIRECT && list)
		printf("mini-shell:	syntax error near unexpected token `>>'\n");
	else
		printf("mini-shell:	syntax error near unexpected token `newline'\n");
}

int redirection_error(t_list *tokens)
{
	t_token	*token;
	t_list	*list;
	t_file	*file;

	list = tokens;
	if(list)
	{
		token = list->content;
		if (token->type != COMMAND && token->type != PIPE)
		{
			file = token->value;
			if (!ft_strlen(file->a_file))
			{
				return (printf_error_redi(token, list->next),1);
			}
		}
	}
	if(list->next)
		redirection_error(list->next);
	return (0);
}

int	syntax_error(char *input, t_list *tokens)
{
	int	i;
	int	boolean;

	i = 0;
	boolean = 1;
	while (boolean && input[i])
		boolean = good_piping(input, &i);
	if (printf_error(boolean))
		return (0);
	if(redirection_error(tokens) > 0)
		return (-1);
	return (1);
}

t_ast	*parser(t_list *tokens, char *input)
{
	t_ast   *tree;
	t_list  **current;

	tree = NULL;
	current = &tokens;
	syntax_error(input, tokens);
	tree = command(current);
	return (tree);
}
