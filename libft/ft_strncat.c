/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:34 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/26 17:36:27 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s2)
		return ;
	while (s1[i])
	{
		i++;
	}
	j = 0;
	while (s2[j] && j < n)
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
}
