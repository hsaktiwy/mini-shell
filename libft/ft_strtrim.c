/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:21:25 by aigounad          #+#    #+#             */
/*   Updated: 2022/10/11 22:53:46 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischarset(char const *set, char c)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		slen;

	if (!s1)
		return (NULL);
	slen = ft_strlen(s1);
	slen--;
	while ((slen > 0) && ischarset(set, s1[slen]))
		slen--;
	slen++;
	while (slen && ischarset(set, *s1))
	{
		s1++;
		slen--;
	}
	p = (char *)malloc(slen + 1);
	if (!p)
		return (NULL);
	p[slen] = '\0';
	while (slen-- > 0)
		p[slen] = s1[slen];
	return (p);
}
