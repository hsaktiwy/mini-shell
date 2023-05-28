/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:28:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 22:01:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
