/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:16:48 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 20:31:31 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	iswhitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	str_iswhitespaced(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if(iswhitespace(str[i]))
			return (1);
		i++;
	}
	return (0);		
}

int	surpace_whitesspaces(char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i] && iswhitespace(str[i]))
		i++;
	(*index) += i;
	return (i);
}
