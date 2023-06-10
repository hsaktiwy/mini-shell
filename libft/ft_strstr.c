/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:46:40 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 20:14:46 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = -1;
	if (haystack && !*haystack)
		return (NULL);
	while (haystack[++i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			{
				j++;
			}
			if (!needle[j])
				return ((char *)&haystack[i]);
		}
	}
	return (NULL);
}
