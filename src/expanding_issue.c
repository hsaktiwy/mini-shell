/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_issue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:53:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/06 19:58:21 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fix_in_cmd(t_cmd **command)
{
	t_cmd	*cmd;
	char	**tab;
	int 	i;

	i = 0;
	cmd = *command;
	tab = ft_split(cmd->cmd, ' ');
	free(cmd->cmd);
	cmd->cmd = tab[0];
	while (tab[i])
		i++;
	if (i - 1 > 0)
	{
		i--;
		while(i > 0 && tab[i])
			ft_lstadd_front(&(cmd->arg), ft_lstnew(tab[i--]));
	}
}

void	fix_in_arg(t_list **arg, char *str, int index)
{
	char	**tab;
	int 	i;

	i = -1;
	tab = ft_split(str, ' ');
	ft_lstdelete_index(arg, index);
	while(tab[++i])
		ft_lstadd_in_index(arg, ft_lstnew(tab[i]), index++);
}

void	fix_if_whitspace(t_cmd **command)
{
	t_cmd		*cmd;
	int			i;
	char		*str;
	t_list		*current;

	i = 0;
	cmd = *command;
	if (str_iswhitespaced(cmd->cmd))
		fix_in_cmd(command);
	current = cmd->arg;
	while (current)
	{
		str = current->content;
		if (str_iswhitespaced(str))
			fix_in_arg(&(cmd->arg), str, i);
		current = current->next;
		i++;
	}
}

void	fix_expanding_issue(t_list **tokens)
{
	t_token	*token;
	t_list	*list;

	list = *tokens;
	while (list)
	{
		token = list->content;
		printf("no\n");
		if (token->type == COMMAND)
			fix_if_whitspace((t_cmd **)&(token->value));
		printf("nope\n");
		list =list->next;
	}
}