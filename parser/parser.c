/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:48:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 14:45:00 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		}else if (input[c] == '|' && open == 1)
			break ;
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

void	printf_error_redi(t_list *list)
{
	t_token *tmp;
	char c [3];

	c[0] = '\0';
	c[1] = '\0';
	c[2] = '\0';
	tmp = NULL;
	if (list)
	{
		tmp = list->content;
		if (tmp->type == 1)
			c[0] = '|';
		else if (tmp->type == 2)
			c[0] = '<';
		else if (tmp->type == 3)
			c[0] = '<';
		else if (tmp->type == 4)
			(c[0] = '<', c[1] = '<');
		else if (tmp->type == 5)
			(c[0] = '>', c[1] = '>');
	}
	if (list && tmp->type != COMMAND && c[0])
	{
		ft_putstr_fd("mini-shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("mini-shell: syntax error near unexpected token `newline'\n", 2);
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
			if (!file->a_file && !ft_strlen(file->token_file))
			{
				if (display != 1)
					return (1);
				return (printf_error_redi(list->next),1);
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
	if (r != 1)
		g_exit_status = 258;
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
		if (err == 1)
		{
			// if (!redirection_habdling(env, tokens))
			// 	return (NULL);
			redirection_habdling(env, tokens);
			list = creat_cmd_list(&current);
		}
	//}
	// printf("number of pipes = %d\n", g_pipe_count(-1));
	return (list);
}
