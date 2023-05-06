/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:42:55 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/06 15:18:22 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	out_red_cmd(t_token **red, t_token **command)
{
	t_cmd   *cmd;
	int		fd;

	fd = -1;
	if (*command)
		cmd = (*command)->value;
	if ((*red)->type == OUT_REDIRECT)
	{
		fd = out_append_red((*red)->value, 0);
		if (cmd->cmd_in == -1)
			return (0); 
	}
	else if ((*red)->type == APPEND_REDIRECT)
	{
		fd = out_append_red((*red)->value, 1);
		if (cmd->cmd_in == -1)
			return (0); 
	}
	if(*command)
		cmd->cmd_out = fd;
	return (1);
}

int	in_red_cmd(t_token **red, t_token **command)
{
	t_cmd   *cmd;
	int		fd;

	fd = -1;
	if(*command)
		cmd = (*command)->value;
	if ((*red)->type == IN_REDIRECT)
	{
		fd = in_redirection((*red)->value);
		if (fd == -1)
			return (0); 
	}
	else if ((*red)->type == HERE_DOC)
	{
		fd = here_doc_red((*red)->value);
		if (fd == -1)
			return (0); 
	}
	if(*command)
		cmd->cmd_in = fd;
	return (1);
}

int	redirect(t_list **list)
{
	t_list  *start;
	t_token *cmd;
	t_token *red;
	t_token *tmp;

	start = *list;
	cmd = NULL;
	while (start)
	{
		tmp = (start)->content;
		if (tmp->type == COMMAND)
			cmd = tmp;
		else if (tmp->type == IN_REDIRECT || tmp->type == HERE_DOC)
		{
			red = tmp;
			if (!in_red_cmd(&red, &cmd))
				return(0);
		}
		else if (tmp->type == OUT_REDIRECT || tmp->type == APPEND_REDIRECT)
		{
			red = tmp;
			if (!out_red_cmd(&red, &cmd))
				return(0);
		}
		else
			break;
		start = (start)->next;
	}
	return (1);
}

void    redirection_habdling(t_list **tokens)
{
	t_list	*list;
	t_token	*token;

	list = *tokens;
	while (list)
	{
		if (!redirect(&list))
			return ;
		while(list)
		{
			token = list->content;
			list = list->next;
			if (token->type == PIPE)
				break;
		}
	}
}
