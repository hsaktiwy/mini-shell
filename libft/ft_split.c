/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:55:40 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 22:01:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lentdusplit(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	numsplits(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j] != c && s[j])
			i++;
		while (s[j] != c && s[j])
			j++;
	}
	return (i);
}

static const char	*nextsplit(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
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

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		numsplit;
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!s)
		return (NULL);
	numsplit = numsplits(s, c);
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
