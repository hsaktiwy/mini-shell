/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:07:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 20:19:59 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->cmd_in = STDIN_FILENO;
	cmd->cmd_out = STDOUT_FILENO;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->error = 0;
	return (cmd);
}

t_token	*last_cmd(t_list **tokens)
{
	t_token	*cmd;
	t_token	*tmp;
	t_list	*list;

	cmd = NULL;
	list = *tokens;
	while (list)
	{
		tmp = list->content;
		if (tmp->type == COMMAND)
			cmd = tmp;
		list = list->next;
	}
	return (cmd);
}
