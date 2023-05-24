/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:17:19 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 14:46:12 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_delimeter(char *line, char *needle)
{
	int	i;

	i = 0;
	if (!(*needle) && *line == '\n')
		return (1);
	while (line[i] && needle[i] && needle[i] == line[i])
		i++;
	if (line[i] == '\0' && !needle[i])
		return (1);
	return (0);
}

int	in_redirection(t_file *tmp)
{
	int fd;

	fd = -1;
	if (tmp->a_file)
	{
		// fd = open(tmp->a_file, O_WRONLY, 0777);
		fd = open(tmp->token_file, O_RDONLY, 0777);
		if (fd == -1)
			print_error(NULL, tmp->a_file, 1);
	}
	else if(ft_strlen(tmp->token_file))
	{
		write(STDERR_FILENO, "minishell : ", 11);
		write(STDERR_FILENO, tmp->token_file, ft_strlen(tmp->token_file));
		write(STDERR_FILENO, ": ambiguous redirect\n", 22);
	}
	return (fd);
}

int	heredoc(t_env *env, char *delimiter, int h_fd)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		g_heredoc_executing(1);
		line = readline("> ");
		if (g_heredoc_executing(-1) && line)
		{
			tmp = expand(env, line);
			if (!find_delimeter(tmp, delimiter) && g_heredoc_executing(-1))
			{
				if (write(h_fd, tmp, ft_strlen(tmp)) == -1
					|| write(h_fd, "\n", 1) == -1)
					return (g_heredoc_executing(0), free(tmp), free(line), 0);
			}
			else
			{
				return (g_heredoc_executing(0), free(tmp), free(line), close(h_fd), 1);
			}
			free(line);
			free(tmp);
			line = NULL;
		}
		else
			return (g_heredoc_executing(0), free(line), 1);
	}
}

int	here_doc_red(t_env *env, t_file *tmp)
{
	int	fd;

	fd = -1;
	if(tmp->a_file)
	{
		// printf(">>>> ? : %s\n",tmp->a_file);
		fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
		// if (!tmp->a_file)
		// 	tmp->a_file = ft_strdup("");
		if (fd == -1)
			print_error(NULL, ".here_doc", 1);
		else if (!heredoc(env, tmp->a_file, fd))
		{
			fd = -1;
			write(2, "Error : here_doc fail\n", 22);
		}
	}
	return (0);		
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
