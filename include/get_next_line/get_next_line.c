/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:01:08 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/05 20:18:43 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_line_exist(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (0);
}

static void	reset(char **s, int start)
{
	int		i;
	char	*re_s;
	char	*str;
	int		size;

	i = -1;
	str = *s;
	size = ft_strlen(*s);
	if (size == start)
	{
		free(*s);
		*s = NULL;
		return ;
	}
	re_s = ft_calloc(size - start + 1);
	while (str[start + (++i)])
		re_s[i] = str[start + i];
	free(*s);
	*s = re_s;
}

static char	*line(char **s, char **buffer)
{
	char	*res;
	char	*str;
	int		start;
	int		i;

	if (buffer)
		free_rest(buffer);
	i = -1;
	str = *s;
	start = ft_strlen_nln(*s);
	res = ft_calloc(start + 1);
	while (++i < start)
		res[i] = str[i];
	reset(s, start);
	return (res);
}

static char	*ft_strjoin_n(char *s1, char *s2)
{
	int		i;
	int		s;
	char	*str;

	i = -1;
	s = 0;
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[++i])
		str[i] = s1[i];
	s = i;
	i = -1;
	while (s2[++i] && s2[i])
		str[s + i] = s2[i];
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_rest(&rest));
	buffer = ft_calloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!rest)
		rest = ft_calloc(1);
	while (read(fd, buffer, BUFFER_SIZE))
	{
		rest = ft_strjoin_n(rest, buffer);
		if (ft_line_exist(rest))
			return (line(&rest, &buffer));
		clean(buffer);
	}
	free_rest(&buffer);
	if (!ft_strlen(rest))
	{
		return (free_rest(&rest));
	}
	return (line(&rest, NULL));
}
