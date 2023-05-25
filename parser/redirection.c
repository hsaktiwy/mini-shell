/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:42:55 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/25 15:45:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_red_cmd(t_token **red, t_token **command)
{
	t_cmd   *cmd;
	int		fd;

	fd = -1;
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

int	in_red_cmd(t_env *env, t_token **red, t_token **command)
{
	t_cmd   *cmd;
	int		fd;

	fd = -1;
	
	if ((*red)->type == IN_REDIRECT)
		fd = in_redirection((*red)->value);
	else if ((*red)->type == HERE_DOC && g_stdin_fd(-1) == -2)
		fd = here_doc_red(env, (*red)->value);
	if (fd == -1)
		return (0);
	if(*command)
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

int	redirect(t_env *env, t_list **list, t_token **cmd)
{
	t_list  *start;
	t_token *red;
	t_token *tmp;

	start = *list;
	while (start)
	{
		tmp = (start)->content;
		if (tmp->type == IN_REDIRECT || tmp->type == HERE_DOC)
		{
			red = tmp;
			if (!in_red_cmd(env, &red, cmd))
				return(0);
		}
		else if (tmp->type == OUT_REDIRECT || tmp->type == APPEND_REDIRECT)
		{
			red = tmp;
			if (!out_red_cmd(&red, cmd))
				return(0);
		}
		else if (tmp->type == PIPE)
			break;
		start = (start)->next;
	}
	return (1);
}

int    redirection_habdling(t_env *env, t_list **tokens)
{
	t_list	*list;
	t_token	*token;
	t_list	*current;
	t_token	*cmd;

	list = *tokens;
	while (list)
	{
		current = list;
		cmd = NULL;
		while (current && !cmd)
		{
			token = current->content;
			if (token->type == COMMAND)
				cmd = token;
			current = current->next;
		}
		if(!redirect(env, &list, &cmd))
			((t_cmd *)cmd->value)->error = 1;
		while(list)
		{
			token = list->content;
			list = list->next;
			if (token->type == PIPE)
				break;
		}
	}
	return (1);
}
