/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:27:52 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/27 22:01:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		len--;
	}
	return (NULL);
}
