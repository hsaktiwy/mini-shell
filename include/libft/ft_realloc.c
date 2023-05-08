/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:50:27 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 16:07:33 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, size_t size)
{
    char	*res;
	char	*str;
    int		i;
	int		j;

    if ((!ptr))
    {
		res = malloc(size);
		return (res);	
	}else if (size > 0)
	{
		res = malloc(size);
		i = -1;
		str = (char *)ptr;
		j = ft_strlen(str);
		while (++i < j)
			res[i] = str[i];
		res[i] = '\0';
		free(ptr);
		return (res);
	}
	return (ptr);
}
