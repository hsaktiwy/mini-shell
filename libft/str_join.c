/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:19:44 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/27 16:37:34 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_join(char *s1, char *s2)
{
	char	*new_str;
	char	*temp;
	int		t[2];

	t[0] = -1;
	t[1] = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	temp = new_str;
	while (s1[++t[0]])
		temp[t[0]] = s1[t[0]];
	while (s2[++t[1]])
		temp[t[0] + t[1]] = s2[t[1]];
	temp[t[0] + t[1]] = '\0';
	return (free(s1), free(s2), new_str);
}
