/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_s_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:12:29 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 18:59:03 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_true_file(t_file *tmp, int *num)
{
	char	**res;

	if (tmp->a_file && (*tmp->a_file))
	{
		res = ft_split(tmp->a_file, '\n');
		*num = ft_t_strlen(res);
		free(tmp->a_file);
		tmp->a_file = ft_strdup(res[0]);
		free_tab(res);
	}
}

int	find_delimeter(char *line, char *needle)
{
	int	i;

	i = 0;
	if (!(*needle) && *line == '\n')
		return (1);
	while (line[i] && needle[i] && needle[i] == line[i])
		i++;
	if (line[i] == '\0' && !needle[i])
		return (1);
	return (0);
}

int	isnext(t_list *current)
{
	t_token	*token;
	t_file	*file;

	token = current->content;
	if (token->type == PIPE)
	{
		if (fack_cmd_next_pipe(current))
			return (0);
	}
	else if (token->type == IN_REDIRECT || token->type == OUT_REDIRECT
		|| token->type == APPEND_REDIRECT)
	{
		file = token->value;
		if (file->a_file == NULL)
			return (0);
	}
	return (1);
}

void	syntax_error_here_doc(t_list **tokens)
{
	t_list	*current;
	t_token	*token;

	current = *tokens;
	if (isfake_cmd(current))
	{
		token = current->next->content;
		if (token->type == PIPE)
			return ;
	}
	while (current)
	{
		token = current->content;
		if (token->type == HERE_DOC)
		{
			if (!in_red_cmd(&token, NULL, 1))
				break ;
		}
		else if (!isnext(current))
			break ;
		current = current->next;
	}
}
