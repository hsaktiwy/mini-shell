/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:21:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 18:51:28 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*get_single_quote(char *s, int *index)
{
	char	c;
	char	*res;
	int		i;
	//int		k;

	i = 0;
	c = '\0';
	res = ft_strdup("");
	while (s[i] && (!c || (c == '\'' && (ft_isprint(s[i]) && !iswhitespace(s[i]) && s[i] != '|'  && s[i] != '<'  && s[i] != '>'))))
	{
		if (s[i] == '\'')
		{
			i++;
			if (!c)
				c = '\'';
			else
				c = '\0';
		}else if (s[i] == '\"' && c == '\'')
		{
			res = ft_strjoin(res, get_double_quote(&s[++i], index));
			break ;
		}
		else if (s[i] && (!c || (c == '\'' && ft_isalnum(s[i]))))
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &s[i], 1);
			i++;
		}
	}
	return ((*index) += i, res);
}
