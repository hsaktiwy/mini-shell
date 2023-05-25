/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:17:59 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/25 14:44:20 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
// #include <ctype.h>
// #include <stdio.h>

int 	is_closed(char *s)
{
	int c;
	int	i;

	i = 0;
	c = '\0';
	while (s[i] && (ft_isalpha(s[i]) || s[i] == '?' || s[i] == '}' || s[i] == '{' ||  s[i] == '_') && c != '}')
	{
		if (s[i] == '{' && c == '\0')
		{
			c = '{';
			i++;
		}
		else if (s[i] == '}' && c == '{')
		{
			c = '}';
			i++;
		}
		else if ((ft_isalpha(s[i]) || s[i] == '?' || s[i] == '_') && (c == '\0' || c == '{'))
			i++;
		else
			break;
	}
	if (c == '}')
		return (i);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	int i;
// 	int res = 0;

// 	char c[200];
// 	while (1)
// 	{
		
// 		printf("gave me ur string :");
// 		scanf("%s", c);
// 		res = is_closed(c);
// 		printf("result is  : %d _ ->(%s)\n", res, &c[res]);
// 	}
// }

char	*expand_env_var(t_env *env, char *s, char *res,int *k)
{
	char	v_env[(*k) + 1];
	char	*re;
	char	*tmp;
	int		size;

	tmp = NULL;
	v_env[0] = '\0';
	if (*s == '{' && is_closed(s) > 0)
	{
		(*k) = is_closed(s);
		char 	tmp_env[(*k) - 1];
		tmp_env[0] = '\0';
		ft_strncat(tmp_env, ++s, (*k) - 2);
		if (ft_strcmp(tmp_env, "?") == 0)
		{
			tmp = ft_itoa(g_exit_status);
			size = ft_strlen(tmp);
			re = ft_realloc(res, ft_strlen(res) + size + 1);
			ft_strncat(re, tmp, size);
			return (free(tmp),re);
		}
		size = ft_strlen(ft_getenv(env, tmp_env));
		re = ft_realloc(res, ft_strlen(res) + size + 1);
		ft_strncat(re, ft_getenv(env, tmp_env), size);
		return (free(tmp),re);
	}
	else
	{
		ft_strncat(v_env, s, *k);
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
	}
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
	while (s[i] && (!c || (c == '\"' && !iswhitespace(s[i]) && s[i] != '|'  && s[i] != '<'  && s[i] != '>')))
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '?' || s[i + 1] == '{'||  s[i + 1] == '_'))
		{
			k = 0;
			while (s[k + i + 1] && s[k + i + 1] != '?' && s[k + i + 1] != '{' && (ft_isalnum(s[k + i + 1]) || s[k + i + 1] == '_'))
				k++;
			if (s[k + i + 1] == '{')
				k++;
			if(s[k + i + 1] == '?')
				k++;
			res = expand_env_var(env, &s[i + 1], res, &k);
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
			res = str_join(res, get_simple_arg(env, &s[i], index));
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
