/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:42:55 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/05 21:44:51 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	find_delimeter(char *line, char *needle)
{
	int	i;

	i = 0;
	while (line[i] && needle[i] && needle[i] == line[i])
		i++;
	if (line[i] == '\n' && !needle[i])
		return (1);
	return (0);
}

int	in_redirection(t_file *tmp)
{
	int fd;

	fd = -1;
	if (ft_strlen(tmp->a_file))
	{
		fd = open(tmp->a_file, O_WRONLY, 0777);
		if (fd == -1)
			perror("mini-shell");
	}
	return (fd);
}

int	heredoc(char *delimiter, int h_fd)
{
	char	*line;

	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line)
		{
			if (!find_delimeter(line, delimiter))
			{
				// EXPAND IN THE HERE_DOC EFORE TROWING TO IT
				if (write(h_fd, line, ft_strlen(line)) == -1)
					return (free(line), 0);
			}
			else
			{
				return (free(line), close(h_fd), 1);
			}
			free(line);
			line = NULL;
		}
		else
			return (1);
	}
}

int	here_doc_red(t_file *tmp)
{
	int	fd;

	fd = -1;
	if(ft_strlen(tmp->a_file))
	{
		// printf(">>>> ? : %s\n",tmp->a_file);
		fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			perror(NULL);
		else if (!heredoc(tmp->a_file, fd))
		{
			fd = -1;
			printf("Error : here_doc fail\n");
		}
	}
	return (fd);		
}

int out_append_red(t_file *tmp, int out_app)
{
	int fd;

	fd = -1;
	if (tmp->a_file)
	{
		if (out_app == 0)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (out_app == 1)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror("mini-shell");
	}
	return (fd);
}

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
