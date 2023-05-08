/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:16:48 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/06 17:45:16 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	iswhitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	str_iswhitespaced(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(iswhitespace(str[i]))
			return (1);
		i++;
	}
	return (0);		
}
