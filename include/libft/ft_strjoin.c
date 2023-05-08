/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:05 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 15:58:40 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*res;
	int		ls1;
	int		ls2;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	res = (char *)malloc(ls1 + ls2 + 1);
	if (!res)
		return (NULL);
	while (i < ls1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (i - ls1 < ls2 && s2[i - ls1])
	{
		res[i] = s2[i - ls1];
		i++;
	}
	res[i] = '\0';
	return (free(s1), free(s2), res);
}
