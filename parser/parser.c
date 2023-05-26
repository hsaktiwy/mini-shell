/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:48:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/26 18:53:54 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error_helper(t_list *list, t_token	*token, int display)
{
	t_file	*file;

	file = token->value;
	if (!file->a_file && !ft_strlen(file->token_file))
	{
		if (display != 1)
			return (1);
		return (printf_error_redi(list->next), 1);
	}
	else if (token->type == HERE_DOC && !file->a_file)
	{
		if (display != 1)
			return (1);
		return (printf_error_redi(list->next), 1);
	}
	return (0);
}

int	redirection_error(t_list *tokens, int display)
{
	t_token	*token;
	t_list	*list;

	list = tokens;
	while (list)
	{
		token = list->content;
		if (token->type != COMMAND && token->type != PIPE)
		{
			if (redirection_error_helper(list, token, display))
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	syntax_error(char *input, t_list *tokens)
{
	int	boolean;
	int	r;

	r = 1;
	boolean = check_piping(input);
	if (printf_error(boolean))
		r *= -1;
	if (redirection_error(tokens, r))
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
		current = current->next;
	}
	return (list);
}

t_list	*parser(t_env *env, t_list **tokens, char *input)
{
	t_list	*list;
	t_list	*current;
	int		err;

	list = NULL;
	current = *tokens;
	err = syntax_error(input, *tokens);
	if (err == 1)
	{
		redirection_habdling(env, tokens);
		list = creat_cmd_list(&current);
	}
	return (list);
}
