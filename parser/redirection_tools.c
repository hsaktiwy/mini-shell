/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:17:19 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/14 15:16:16 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_redirection(t_file *tmp)
{
	int		fd;
	int		num;

	num = 1;
	get_true_file(tmp, &num);
	fd = -1;
	if (num == 1 && tmp->a_file)
	{
		fd = open(tmp->a_file, O_RDONLY, 0777);
		if (fd == -1)
			print_error(tmp->a_file, NULL, 1);
	}
	else if (ft_strlen(tmp->token_file))
		display_ambiguise(tmp);
	return (fd);
}

int	heredoc_helper(char *line, int h_fd, int exp)
{
	char	*tmp;

	if (exp)
		tmp = expand(line);
	else
		tmp = line;
	if (write(h_fd, tmp, ft_strlen(tmp)) == -1
		|| write(h_fd, "\n", 1) == -1)
		return (free(tmp), 0);
	if (exp)
		return (free(tmp), 1);
	return (1);
}

int	heredoc(char *delimiter, int h_fd, int exp)
{
	char	*line;

	while (1)
	{
		g_heredoc_executing(1);
		line = get_line();
		if (g_heredoc_executing(-1) && line)
		{
			if (!find_delimeter(line, delimiter) && g_heredoc_executing(-1))
			{
				if (!heredoc_helper(line, h_fd, exp))
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

int	here_doc_red(t_file *tmp)
{
	int	fd;

	fd = -1;
	if (tmp->a_file)
	{
		if (tmp->token_file)
		{
			unlink(tmp->token_file);
			fd = open(tmp->token_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		if (fd == -1)
		{
			print_error(NULL, tmp->token_file, 1);
			return (-1);
		}
		else if (!heredoc(tmp->a_file, fd, tmp->here_doc_exp))
		{
			write(STDERR_FILENO, "minishell : Error: here_doc fail\n", 33);
			return (-1);
		}
	}
	else
		return (-1);
	return (0);
}

int	out_append_red(t_file *tmp, int out_app)
{
	int		fd;
	int		num;

	fd = -1;
	num = 1;
	get_true_file(tmp, &num);
	if (out_app == OUT_REDIRECT)
	{
		if (num == 1 && tmp->a_file)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (ft_strlen(tmp->token_file))
			return (display_ambiguise(tmp), -1);
	}
	else if (out_app == APPEND_REDIRECT)
	{
		if (num == 1 && tmp->a_file)
			fd = open(tmp->a_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (ft_strlen(tmp->token_file))
			return (display_ambiguise(tmp), -1);
	}
	if (fd == -1)
		print_error(tmp->a_file, NULL, 1);
	return (fd);
}
