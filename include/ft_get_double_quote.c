/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:17:59 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 18:50:45 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*expand_env_var(char *s, char *res,int k)
{
	char	env[k + 1];
	char	*re;
	int		size;

	env[0] = '\0';
	ft_strncat(env, s, k);
	size = ft_strlen(getenv(env));
	re = ft_realloc(res, ft_strlen(res) + size + 1);
	ft_strncat(re, getenv(env), size);
	return (re);
}

char	*get_double_quote(char *s, int *index)
{
	char c;
	char *res;
	int i;
	int k;

	i = 0;
	c = '\0';
	res = ft_strdup("");
	while (s[i] && (!c || (c == '\"' && (ft_isprint(s[i]) && !iswhitespace(s[i]) && s[i] != '|'  && s[i] != '<'  && s[i] != '>'))))
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '?' ||  s[i + 1] == '_'))
		{
			k = 0;
			while (s[k + i + 1] && (ft_isalnum(s[k + i + 1])|| s[k + i + 1] == '?' || s[k + i + 1] == '_'))
				k++;
			res = expand_env_var(&s[i + 1], res, k);
			i += k + 1;
		}
		else if (s[i] == '\"')
		{
			if(!c)
				c = '\"';
			else
				c = '\0';
			i++;
		}else if (s[i] == '\'' && c == '\"')
		{
			res = ft_strjoin(res, get_single_quote(&s[++i], index));
			break ;
		}
		else if (s[i] && (!c || (c == '\"' && ft_isalnum(s[i]))))
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &s[i], 1);
			i++;
		}
	}
	return ((*index) += i, res);
}
