/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:17:59 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 14:07:33 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*expand_env_var(t_env *env, char *s, char *res,int k)
{
	char	v_env[k + 1];
	char	*re;
	char	*tmp;
	int		size;

	v_env[0] = '\0';
	ft_strncat(v_env, s, k);
	// printf("before adding to : %s\n",ft_getenv(env, v_env));
	if (ft_strcmp(v_env, "?") == 0)
	{
		tmp = ft_itoa(g_exit_status);
		size = ft_strlen(tmp);
		re = ft_realloc(res, ft_strlen(res) + size + 1);
		ft_strncat(re, tmp, size);
		return (free(tmp), re);
	}
	size = ft_strlen(ft_getenv(env, v_env));
	re = ft_realloc(res, ft_strlen(res) + size + 1);
	ft_strncat(re, ft_getenv(env, v_env), size);
	return (re);
}

char	*get_double_quote(t_env *env, char *s, int *index)
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
			while (s[k + i + 1] && (ft_isalnum(s[k + i + 1])|| s[k + i + 1] != '?' || s[k + i + 1] == '_'))
				k++;
			if(s[k + i + 1] == '?')
				k++;
			res = expand_env_var(env, &s[i + 1], res, k);
			i += k + 1;
		}
		else if (s[i] == '\"')
		{
			if(!c)
				c = '\"';
			else
				c = '\0';
			i++;
		}else if (c == '\"')
		{
			//(*index) += i;
			// printf("from double to -> get_simple_arg(%s)(%d)\n",&s[i], *index);
			res = ft_strjoin(res, get_simple_arg(env, &s[i], index));
			break ;
		}
		else if (s[i] && !c)
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &s[i], 1);
			i++;
		}
		// printf("??? = %c _ %s(c == [%c])\n", s[i], res, c);
	}
	// printf("final result : |%s|\n", res);
	return ((*index) += i, res);
}
