/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:13:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 20:18:37 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_red_cmd(t_token **red, t_token **command, int r)
{
	t_cmd	*cmd;
	int		fd;

	fd = -1;
	if (r == 1)
		fd = out_append_red((*red)->value, (*red)->type);
	if (fd == -1)
		return (0);
	if (*command)
	{
		cmd = (*command)->value;
		cmd->cmd_out = fd;
		cmd->file_out = ((t_file *)((*red)->value))->a_file;
	}	
	return (1);
}

int	in_red_cmd(t_token **red, t_token **command, int r)
{
	t_cmd	*cmd;
	int		fd;

	fd = -1;
	if ((*red)->type == IN_REDIRECT && r == 1)
		fd = in_redirection((*red)->value);
	else if ((*red)->type == HERE_DOC && g_stdin_fd(-1) == 0)
		fd = here_doc_red((*red)->value);
	if (fd == -1)
		return (0);
	if (command && *command)
	{
		cmd = (*command)->value;
		cmd->cmd_in = fd;
		if ((*red)->type == HERE_DOC)
			cmd->file_in = ((t_file *)((*red)->value))->token_file;
		else
			cmd->file_in = ((t_file *)((*red)->value))->a_file;
	}
	return (1);
}

int	redirect(t_list **list, t_token **cmd)
{
	t_list	*start;
	t_token	*tmp;
	int		r;

	r = 1;
	start = *list;
	while (start)
	{
		tmp = (start)->content;
		if (tmp->type == IN_REDIRECT || tmp->type == HERE_DOC)
		{
			if (!in_red_cmd(&tmp, cmd, r) && r == 1)
				r = 0;
		}
		else if (tmp->type == OUT_REDIRECT || tmp->type == APPEND_REDIRECT)
		{
			if (!out_red_cmd(&tmp, cmd, r) && r == 1)
				r = 0;
		}
		else if (tmp->type == PIPE)
			break ;
		start = (start)->next;
	}
	return (r);
}

int	redirection_hanbdling(t_list **tokens)
{
	t_list	*list;
	t_token	*token;
	t_token	*cmd;

	list = *tokens;
	while (list)
	{
		cmd = next_cmd(list);
		if (!redirect(&list, &cmd))
		{
			((t_cmd *)cmd->value)->error = 1;
			g_exit_status = 1;
		}
		while (list)
		{
			token = list->content;
			list = list->next;
			if (token->type == PIPE)
				break ;
		}
	}
	return (1);
}
