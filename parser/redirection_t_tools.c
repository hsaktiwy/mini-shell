/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_t_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:47:47 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 19:27:11 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	display_ambiguise(t_file	*tmp)
{
	write(STDERR_FILENO, "minishell : ", 12);
	write(STDERR_FILENO, tmp->token_file,
		ft_strlen(tmp->token_file));
	write(STDERR_FILENO, ": ambiguous redirect\n", 21);
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

char	*get_line(void)
{
	char	*line;
	char	*res;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
	{
		res = get_next_line(STDIN_FILENO);
		line = ft_strtrim(res, "\n");
		free(res);
	}
	return (line);
}
