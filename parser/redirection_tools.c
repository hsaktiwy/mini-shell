/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:17:19 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 15:12:55 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_redirection(t_file *tmp)
{
	int	fd;

	fd = -1;
	if (tmp->a_file)
	{
		fd = open(tmp->a_file, O_RDONLY, 0777);
		if (fd == -1)
			print_error(NULL, tmp->a_file, 1);
	}
	else if (ft_strlen(tmp->token_file))
	{
		write(STDERR_FILENO, "minishell : ", 11);
		write(STDERR_FILENO, tmp->token_file, ft_strlen(tmp->token_file));
		write(STDERR_FILENO, ": ambiguous redirect\n", 22);
	}
	return (fd);
}

int	heredoc_helper(t_env *env, char *line, int h_fd, int exp)
{
	char	*tmp;

	if (exp)
		tmp = expand(env, line);
	else
		tmp = line;
	if (write(h_fd, tmp, ft_strlen(tmp)) == -1
		|| write(h_fd, "\n", 1) == -1)
		return (free(tmp), 0);
	if (exp)
		return (free(tmp), 1);
	return (1);
}

int	heredoc(t_env *env, char *delimiter, int h_fd, int exp)
{
	char	*line;

	while (1)
	{
		g_heredoc_executing(1);
		line = readline("> ");
		if (g_heredoc_executing(-1) && line)
		{
			if (!find_delimeter(line, delimiter) && g_heredoc_executing(-1))
			{
				if (!heredoc_helper(env, line, h_fd, exp))
					return (g_heredoc_executing(0),
						free(line), close(h_fd), 0);
			}
			else
				return (g_heredoc_executing(0), free(line), close(h_fd), 1);
			free(line);
			line = NULL;
		}
		else
			return (g_heredoc_executing(0), free(line), close(h_fd), 1);
	}
}

int	here_doc_red(t_env *env, t_file *tmp)
{
	int	fd;

	fd = -1;
	if (tmp->a_file)
	{
		if (tmp->token_file)
		fd = open(tmp->token_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
				g_exit_status = 1;
			if (errno == EACCES)
				g_exit_status = 1;
			else if (errno == ENOENT)
				g_exit_status = 1;
			print_error(NULL, tmp->token_file, 1);
		}
		else if (!heredoc(env, tmp->a_file, fd, tmp->here_doc_exp))
		{
			fd = -1;
			write(2, "Error : here_doc fail\n", 22);
		}
	}
	return (0);
}

int	out_append_red(t_file *tmp, int out_app)
{
	int	fd;

	fd = -1;
	if (tmp->a_file)
	{
		if (out_app == OUT_REDIRECT)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (out_app == APPEND_REDIRECT)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			print_error(NULL, tmp->a_file, 1);
	}
	return (fd);
}
