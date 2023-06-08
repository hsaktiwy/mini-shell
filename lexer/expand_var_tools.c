/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:17:59 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/08 02:37:15 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_closed_helper(char s, char *c, int *i)
{
	if (s == '{' && *c == '\0')
	{
		*c = '{';
		(*i)++;
	}
	else if (s == '}' && *c == '{')
	{
		*c = '}';
		(*i)++;
	}
	else if ((ft_isalpha(s) || s == '?' || s == '_')
		&& (*c == '\0' || *c == '{'))
		(*i)++;
	else
		return (0);
	return (1);
}

int	is_closed(char *s)
{
	char	c;
	int		i;

	i = 0;
	c = '\0';
	while (s[i] && (ft_isalpha(s[i]) || s[i] == '?' || s[i] == '}'
			|| s[i] == '{' || s[i] == '_') && c != '}')
	{
		if (!is_closed_helper(s[i], &c, &i))
			break ;
	}
	if (c == '}')
		return (i);
	return (0);
}

char	*expand_nor_var(char *res, char *v_env, char *s, int *k)
{
	char	*tmp;
	int		size;
	char	*re;

	ft_strncat(v_env, s, *k);
	if (ft_strcmp(v_env, "?") == 0)
	{
		tmp = ft_itoa(g_exit_status);
		size = ft_strlen(tmp);
		re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
		ft_strncat(re, tmp, size);
		return (free(tmp), re);
	}
	tmp = ft_getenv(g_env_s(NULL), v_env);
	if (tmp)
		tmp = encapsulation(tmp);
	size = ft_strlen(tmp);
	re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
	ft_strncat(re, tmp, size);
	return (free(tmp), re);
}

char	*expand_in_brace(char	*s, int *k, char *res)
{
	char	*tmp;
	int		size;
	char	*tmp_env;
	char	*re;

	tmp_env = malloc((*k));
	(*k) = is_closed(s);
	tmp_env[0] = '\0';
	ft_strncat(tmp_env, ++s, (*k) - 2);
	if (ft_strcmp(tmp_env, "?") == 0)
	{
		tmp = ft_itoa(g_exit_status);
		size = ft_strlen(tmp);
		re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
		ft_strncat(re, tmp, size);
		return (free(tmp_env), free(tmp), re);
	}
	tmp = ft_getenv(g_env_s(NULL), tmp_env);
	if (tmp)
		tmp = encapsulation(tmp);
	size = ft_strlen(tmp);
	re = ft_realloc(res, ft_strlen(res) + size + 1 + 2);
	ft_strncat(re, tmp, size);
	return (free(tmp_env), free(tmp), re);
}

char	*expand_env_var(char *s, char *res, int *k)
{
	char	*v_env;
	// char	*tmp;

	// tmp = NULL;
	v_env = malloc((*k) + 1);
	v_env[0] = '\0';
	if (*s == '{' && is_closed(s) > 0)
		return (free(v_env), expand_in_brace(s, k, res));
	else
		return (free(v_env), expand_nor_var(res, v_env, s, k));
}
