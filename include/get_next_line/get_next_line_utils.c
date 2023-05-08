/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:01:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/05 20:17:03 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

size_t	ft_strlen_nln(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	clean(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		s[i++] = 0;
}

void	*ft_calloc(size_t	count)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(count);
	while (i < count)
		res[i++] = 0;
	return (res);
}

void	*free_rest(char **rest)
{
	free(*rest);
	*rest = NULL;
	return (NULL);
}
