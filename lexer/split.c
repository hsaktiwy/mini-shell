/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:55:40 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/05 11:47:11 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	lentdusplit(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	numsplits(const char *s)
{
	int		i;
	int		counter;
	char	c;
	char	c_tmp;

	c = '\0';
	counter = 0;
	i = 0;
	while (s[i])
	{
		c_tmp = c;
		if (s[i] == '\'' || s[i] == '\"')
			c = double_or_single(s[i], c);
		if (!c && c_tmp != c &&  s[i + 1] && iswhitespace(s[i + 1]))
			counter++;
		i++;
	}
	return (counter);
}

static const char	*nextsplit(const char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == 32)
		i++;
	return ((char *)&s[i]);
}

static char	*splited(char **bres, char *res, const char *s, int size)
{
	res = ft_substr(s, 0, size);
	if (!res)
	{
		while (*bres)
			free(*bres++);
		free(bres);
	}
	return (res);
}

char	**ft_split(char const *s)
{
	char	**res;
	int		numsplit;
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!s)
		return (NULL);
	numsplit = numsplits(s);
	res = (char **)malloc((numsplit + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < numsplit)
	{
		s = nextsplit(&s[size], c);
		size = lentdusplit(s, c);
		res[i] = splited(res, res[i], s, size);
		if (!res[i++])
			return (NULL);
	}
	res[i] = NULL;
	return (res);
}
