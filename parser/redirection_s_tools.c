/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_s_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:12:29 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/04 19:19:46 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_true_file(t_file *tmp, int *num)
{
	char	**res;

	if (tmp->a_file)
	{
		res = ft_split(tmp->a_file, '\n');
		*num = ft_t_strlen(res);
		free(tmp->a_file);
		tmp->a_file = ft_strdup(res[0]);
		fre_tab(res);
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

int	isfake_cmd(t_list	*list)
{
	t_token	*tmp;
	t_cmd	*cmd;

	if (!list)
		return (-1);
	tmp = list->content;
	if (tmp->type == COMMAND)
	{
		cmd = tmp->value;
		if (cmd->cmd == NULL)
			return (1);
	}
	return (0);
}

int	fack_cmd_next_pipe(t_list *current)
{
	t_token	*tmp;

	if (isfake_cmd(current->next))
	{
		if (current->next->next)
		{
			tmp = current->next->next->content;
			if (tmp->type == PIPE)
				return (1);
		}
	}
	return (0);
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
			if (!in_red_cmd(g_env_s(NULL), &token, NULL))
				break ;
		}
		else if (token->type == PIPE)
			if (fack_cmd_next_pipe(current))
				break ;
		current = current->next;
	}
}
