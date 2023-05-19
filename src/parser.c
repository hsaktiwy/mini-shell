/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:48:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/19 18:35:03 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int check_piping(char *input)
{
	int	c;
	int	open;

	open = -1;
	c = 0;
	if (input[c] == '|')
		return (0);
	while (input[c] && ft_isprint(input[c]))
	{
		if (input[c] == '|' && open != 1)
		{
			open = 1;
		}
		else if (input[c] != '|' && !iswhitespace(input[c]) && open == 1)
		{
			open = 0;
		}
		c++;
	}
	if (open == 1)
		return (0);
	return (1);
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

int redirection_error(t_list *tokens, int display)
{
	t_token	*token;
	t_list	*list;
	t_file	*file;

	list = tokens;
	while (list)
	{
		token = list->content;
		if (token->type != COMMAND && token->type != PIPE)
		{
			file = token->value;
			if (!file->a_file)
			{
				if (display != 1)
					return (1);
				return (printf_error_redi(token, list->next),1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	syntax_error(char *input, t_list *tokens)
{
	int	boolean;
	int r;
	
	r = 1;
	boolean = check_piping(input);
	if (printf_error(boolean))
		r *= -1;
	if(redirection_error(tokens, r))
		r += -1;
	return (r);
}

t_list	*creat_cmd_list(t_list	**tokens)
{
	t_list	*list;
	t_list	*current;
	t_token	*token;

	current = *tokens;
	list = NULL;
	while (current)
	{
		token = current->content;
		if (token->type == COMMAND)
		{
			ft_lstadd_back(&list, ft_lstnew(token));
		}
		// ls | >out problem to solve
		// else if (token->type == PIPE)
		// {
		// 	ft_lstadd_back(&list, ft_lstnew(token));
		// }
		current = current->next;
	}
	return (list);
}

t_list	*parser(t_env *env, t_list **tokens, char *input)
{
	t_list   *list;
	t_list  *current;
	int		err;

	list = NULL;
	current = *tokens;
	err = syntax_error(input, *tokens);
	// if (err != -1)
	// {
		//printf("Error : %d\n", err);
		if (!redirection_habdling(env, tokens))
			return (NULL);
		if (err == 1)
			list = creat_cmd_list(&current);
	//}
	return (list);
}
