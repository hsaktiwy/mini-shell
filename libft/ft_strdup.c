/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:28:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/11 12:28:32 by aigounad         ###   ########.fr       */
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
