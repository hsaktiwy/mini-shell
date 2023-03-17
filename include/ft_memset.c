/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:16:10 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 08:00:03 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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