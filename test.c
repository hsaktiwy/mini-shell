/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:34:56 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/29 16:33:01 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//#include "include/libft.h"
# include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	x;
	size_t			i;
	char			*str;

	x = (unsigned char)c;
	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = x;
		i++;
	}
	return (b);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*res;

	i = 0;
	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	res = (char *) malloc(size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ft_memset(sub, '\0', len);
		return (sub);
	}
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

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

static void	free_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}
int isendwith(char *string)
{
	int i;

	if (string)
	{
		i = ft_strlen(string);
		if (string[i - 1] == '*')
			return (1);
	}
	return (0);
}

int	ft_regx(char *string, char *exp)
{
	char **points;
	char *tmp;
	int	i;
	int		corr;

	corr = 1;
	i = 0;
	tmp = string;
	points = ft_split(exp, '*');
	while (points[i])
	{
		printf("%s\n",points[i]);
		i++;
	}
	i = 0;
	printf("tmp = %s\n",string);
	while (tmp && *tmp && points[i])
	{
		tmp = strstr(tmp, points[i]);
		printf("s = %s\n",tmp);
		i++;
	}
	if (!tmp)
		return (free_tab(points), 0);
	// printf("%d\n",isendwith(exp));
	// if (!points[i] && exp[0] != '*' && !isendwith(exp))
	// {
	// 	tmp = strstr(string, points[0]);
	// 	if (tmp && !isendwith(exp) && string == tmp)
	// 	{
	// 		tmp = strstr(string, points[i - 1]);
	// 		tmp = &tmp[strlen(points[i - 1])];
	// 		printf("%c\n", *tmp);
	// 		if (!*tmp)
	// 			return (free_tab(points), 1);
	// 	}
	// 	else if (tmp && string == tmp)
	// 		return (free_tab(points), 1);
	// }
	// if (!points[i] && exp[0] != '*' && isendwith(exp))
	// {
	// 	tmp = strstr(string, points[0]);
	// 	if (tmp && string == tmp)
	// 		return (free_tab(points), 1);
	// }
	// else if (!points[i] && !isendwith(exp))
	// {
	// 	if (tmp)
	// 	{
	// 		tmp = &tmp[strlen(points[i - 1])];
	// 		printf("%c\n", *tmp);
	// 		if (!*tmp)
	// 			return (free_tab(points), 1);
	// 	}
	// }
	// else if (!points[i])
	// 	return (free_tab(points), 1);
	if (!points[i] && exp[0] != '*' && corr)
	{
		tmp = strstr(string, points[0]);
		if (string < tmp)
			corr = 0;
	}
	printf("corr =%d\n", corr);
	if (!points[i] && !isendwith(exp) && corr)
	{
		tmp = string;
		while (strstr(&tmp[1], points[i - 1]))
		{
			tmp = strstr(&tmp[1], points[i - 1]);
		}
		tmp = &tmp[ft_strlen(points[i - 1])];
		if (*tmp)
			corr = 0;
	}
	return (free_tab(points), corr);
}
int main(int argc, char **argv)
{
	if (argc == 3)
		printf("%d\n", ft_regx(argv[1], argv[2]));
	return (0);
}
