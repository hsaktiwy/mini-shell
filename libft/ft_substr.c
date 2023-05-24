/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:19:26 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 08:02:36 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
