/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_issue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:53:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 16:10:04 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fix_in_cmd(t_cmd **command)
// {
// 	t_cmd	*cmd;
// 	char	**tab;
// 	int		i;

// 	i = 0;
// 	cmd = *command;
// 	tab = ft_split(cmd->cmd, ' ');
// 	free(cmd->cmd);
// 	cmd->cmd = tab[0];
// 	while (tab[i])
// 		i++;
// 	if (i - 1 > 0)
// 	{
// 		i--;
// 		while (i > 0 && tab[i])
// 			ft_lstadd_front(&(cmd->arg), ft_lstnew(creat_arg(tab[i--], WORD)));
// 	}
// }

// void	fix_in_arg(t_list **arg, t_file *str, int index)
// {
// 	char	**tab;
// 	int		i;

// 	i = -1;
// 	tab = ft_split(str->a_file, ' ');
// 	ft_lstdelete_index(arg, index, ft_lstfree_t_file);
// 	while (tab[++i])
// 	{
// 		ft_lstadd_in_index(arg,
// 			ft_lstnew(creat_arg(tab[i], WORD)), index++);
// 	}
// }

// void	fix_if_whitspace(t_cmd **command)
// {
// 	t_cmd		*cmd;
// 	int			i;
// 	t_file		*str;
// 	t_list		*current;

// 	i = 0;
// 	cmd = *command;
// 	if (str_iswhitespaced(cmd->cmd)
// 		&& cmd->cmd_type == VARIABLE)
// 		fix_in_cmd(command);
// 	current = cmd->arg;
// 	while (current)
// 	{
// 		str = current->content;
// 		if (str->a_file && str_iswhitespaced(str->a_file)
// 			&& str->arg_type == VARIABLE)
// 		{
// 			fix_in_arg(&(cmd->arg), str, i);
// 			current = cmd->arg;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// }

// void	fix_expanding_issue(t_list **tokens)
// {
// 	t_token	*token;
// 	t_list	*list;

// 	list = *tokens;
// 	while (list)
// 	{
// 		token = list->content;
// 		if (token->type == COMMAND)
// 			fix_if_whitspace((t_cmd **)&(token->value));
// 		list = list->next;
// 	}
// }
