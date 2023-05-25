/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:21:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/25 14:44:40 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_single_quote(t_env *env, char *s, int *index)
{
	char	c;
	char	*res;
	int		i;

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
		}else if (c == '\'')
		{
			res = str_join(res, get_simple_arg(env, &s[i], index));
			break ;
		}
		else if (s[i] && !c)
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &s[i], 1);
			i++;
		}
	}
	return ((*index) += i, res);
}
