/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:40:58 by aigounad          #+#    #+#             */
/*   Updated: 2022/10/11 17:53:12 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	r;
	long int	s;
	int			sign;

	r = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		s = r;
		r = r * 10 + (*str - '0');
		if (s != (r / 10) && sign == -1)
			return (0);
		if (s != (r / 10) && sign == 1)
			return (-1);
		str++;
	}
	return ((int)(r * sign));
}
