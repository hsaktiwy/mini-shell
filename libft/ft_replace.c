/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:56:22 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/04 19:20:28 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace(void *str, char old, char new)
{
	int		i;
	char	*tmp;

	tmp = str;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == old)
			tmp[i] = new;
		i++;
	}
}
