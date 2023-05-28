/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:24:18 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/27 22:01:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += 1;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = num_size(n);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	ptr[size--] = '\0';
	if (n < 0)
	{
		*ptr = '-';
		n *= -1;
		i = 1;
	}
	while (size >= i)
	{
		ptr[size--] = (n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}
