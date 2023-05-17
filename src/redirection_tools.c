/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:17:19 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/17 15:45:45 by hsaktiwy         ###   ########.fr       */
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
		if (ft_strlen(tmp->a_file) != 0)
			fd = open(tmp->a_file, O_WRONLY, 0777);
		if (fd == -1)
			print_error(NULL, tmp->a_file, 1);
	}
	return (fd);
}

int	heredoc(t_env *env, char *delimiter, int h_fd)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line)
		{
			tmp = expand(env, line);
			if (!find_delimeter(tmp, delimiter))
			{
				if (write(h_fd, tmp, ft_strlen(tmp)) == -1)
					return (free(tmp), free(line), 0);
			}
			else
			{
				return (free(tmp), free(line), close(h_fd), 1);
			}
			free(line);
			free(tmp);
			line = NULL;
		}
		else
			return (1);
	}
}

int	here_doc_red(t_env *env, t_file *tmp)
{
	int	fd;

	fd = -1;
	if(ft_strlen(tmp->a_file))
	{
		// printf(">>>> ? : %s\n",tmp->a_file);
		fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			print_error(NULL, ".here_doc", 1);
		else if (!heredoc(env, tmp->a_file, fd))
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
		if (out_app == OUT_REDIRECT)
		{
			if (ft_strlen(tmp->a_file) != 0)
				fd = open(tmp->a_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		else if (out_app == APPEND_REDIRECT)
		{
			if (ft_strlen(tmp->a_file) != 0)
				fd = open(tmp->a_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		if (fd == -1)
			print_error(NULL, tmp->a_file, 1);
	}
	return (fd);
}
