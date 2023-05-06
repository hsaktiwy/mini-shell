/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:17:19 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/06 15:18:18 by hsaktiwy         ###   ########.fr       */
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
