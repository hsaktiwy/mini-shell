/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:17:59 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/05 20:18:05 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
// #include <ctype.h>
// #include <stdio.h>

int	is_closed(char *s)
{
	int	c;
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
			break ;
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
char	*add_back(char *arg, char *input, char *c)
{
	char	*res;

	res = ft_realloc(arg, ft_strlen(arg) + 3);
	ft_strncat(res, input, 1);
	if (input[0] == '\'')
		ft_strncat(res, "\"", 1);
	else
		ft_strncat(res, "\'", 1);
	*c = double_or_single(input[0], *c);
	return (res);
}

char	*add_front(char *arg, char *input, char *c)
{
	char	*res;

	res = ft_realloc(arg, ft_strlen(arg) + 3);
	if (input[0] == '\'')
		ft_strncat(res, "\"", 1);
	else
		ft_strncat(res, "\'", 1);
	ft_strncat(res, input, 1);
	*c = double_or_single(input[0], *c);
	return (res);
}

char	*encapsulation(char *str)
{
	int		i;
	char	*res;
	char	c;

	i = -1;
	c = '\0';
	res = ft_strdup("");
	while (str[++i])
	{
		if (!c && (str[i] == '\'' || str[i] == '\"'))
			res = add_front(res, &str[i], &c);
		else if (c && c == str[i])
			res = add_back(res, &str[i], &c);
		else
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &str[i], 1);
		}
	}
	return (res);
}

char	*expand_env_var(t_env *env, char *s, char *res, int *k)
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
			re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
			ft_strncat(re, tmp, size);
			return (free(tmp), re);
		}
		tmp = ft_getenv(env, tmp_env);
		if (tmp)
			tmp = encapsulation(tmp);
		size = ft_strlen(tmp);
		re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
		ft_strncat(re, tmp, size);
		return (free(tmp), re);
	}
	else
	{
		ft_strncat(v_env, s, *k);
		if (ft_strcmp(v_env, "?") == 0)
		{
			tmp = ft_itoa(g_exit_status);
			size = ft_strlen(tmp);
			re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
			ft_strncat(re, tmp, size);
			return (free(tmp), re);
		}
		tmp = ft_getenv(env, v_env);
		if (tmp)
			tmp = encapsulation(tmp);
		size = ft_strlen(tmp);
		re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
		ft_strncat(re, tmp, size);
	}
	return (free(tmp), re);
}

char	*get_double_quote(t_env *env, char *s, int *index)
{
	char c;
	char *res;
	int i;
	// int k;

	i = 0;
	c = '\0';
	res = ft_strdup("");
	while (s[i] && (!c || (c == '\"' && !iswhitespace(s[i]) && s[i] != '|'  && s[i] != '<'  && s[i] != '>')))
	{
		// if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '?' || s[i + 1] == '{'||  s[i + 1] == '_'))
		// {
		// 	k = 0;
		// 	while (s[k + i + 1] && s[k + i + 1] != '?' && s[k + i + 1] != '{' && (ft_isalnum(s[k + i + 1]) || s[k + i + 1] == '_'))
		// 		k++;
		// 	if (s[k + i + 1] == '{')
		// 		k++;
		// 	if(s[k + i + 1] == '?')
		// 		k++;
		// 	res = expand_env_var(env, &s[i + 1], res, &k);
		// 	i += k + 1;
		// }
		// else 
		if (s[i] == '\"')
		{
			if(!c)
				c = '\"';
			else
				c = '\0';
			i++;
		}
		else if (c == '\"')
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
