/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:44:05 by aigounad          #+#    #+#             */
/*   Updated: 2023/01/10 15:10:10 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_accept(char *s)
{
	char	*p;
	int		i;

	i = 0;
	if (!ft_strchr(s, '\n'))
		return (s);
	while (s[i] != '\n')
		i++;
	i++;
	p = ft_substr(s, 0, i);
	return (p);
}

static char	*ft_reject(char *s)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!ft_strchr(s, '\n'))
		return (NULL);
	while (s[i] != '\n')
		i++;
	if (s[i + 1] == '\0')
	{
		free(s);
		return (NULL);
	}
	i++;
	p = ft_substr(s, i, ft_strlen(s) - i);
	free(s);
	return (p);
}

static char	*ft_read_file(int fd, char *strs, int *eof)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes;
	char	*tmp;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes < 0)
	{
		*eof = -1;
		free(strs);
		return (NULL);
	}
	if (bytes == 0)
	{
		*eof = 1;
		return (strs);
	}
	buf[bytes] = '\0';
	tmp = ft_strjoin(strs, buf);
	free(strs);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*strs;
	int			eof;
	char		*line;

	eof = 0;
	if ((read(fd, NULL, 0) < 0) || BUFFER_SIZE <= 0 || fd < 0)
	{
		free(strs);
		strs = NULL;
		return (NULL);
	}
	while (!ft_strchr(strs, '\n') && eof == 0)
		strs = ft_read_file(fd, strs, &eof);
	if (eof == -1)
		return (NULL);
	line = ft_accept(strs);
	strs = ft_reject(strs);
	return (line);
}
