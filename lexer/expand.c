/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:37:42 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/06 13:56:58 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(t_env *env, char *line)
{
	int		i;
	int		k;
	char	*arg;

	i = 0;
	arg = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalpha(line[i + 1]) || line[i + 1] == '{' || line[i + 1] == '?' ||  line[i + 1] == '_') && !iswhitespace(line[i + 1]))
		{
			k = 0;
			while (line[k + i + 1] && line[k + i + 1] != '?' && line[k + i + 1] != '{' && (ft_isalnum(line[k + i + 1]) || line[k + i + 1] == '_'))
				k++;
			if (line[k + i + 1] == '?')
				k++;
			arg = expand_env_var(env , &line[i + 1], arg, &k);
			i += k + 1;
		}
		else if (line[i])
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i], 1);
			i++;
		}
	}
	return (arg);
}

char	*reallocated_str(char *str, char *add)
{
	int		size;
	char	*res;

	size = ft_strlen(add);
	res = ft_realloc(str, ft_strlen(str) + size + 1);
	ft_strncat(res, add, size);
	return (res);
}

char	*remove_white_spaces(char *p)
{
	char	*tmp;

	tmp = p;
	p = ft_strtrim(tmp, " ");
	free(tmp);
	//g_input_line(p);
	return (p);
}

// char    *expand_input(t_env *env, char *line)
// {
// 	int		i;
// 	char 	c;
// 	int		s;
// 	char	*arg;

// 	i = 0;
// 	c = '\0';
// 	arg = ft_strdup("");
// 	s = 0;
// 	while (line[i])
// 	{
// 		if ((line[i] == '~' && (iswhitespace(line[i + 1])
// 			|| line[i + 1] == '\0' || line[i + 1] == '/') && c == '\0'))
// 		{
// 			if (ft_getenv(env, "HOME"))
// 				arg = reallocated_str(arg, ft_getenv(env, "HOME"));
// 			else
// 			{
// 				arg = ft_realloc(arg, ft_strlen(arg) + 2);
// 				ft_strncat(arg, &line[i], 1);
// 			}
// 			i++;
// 		}
// 		else if (line[i])
// 		{
// 			if (line[i] == '\'' && c == '\0')
// 				c = '\'';
// 			else if (line[i] == '\"' && c == '\0')
// 				c = '\"';
// 			else if (line[i] == '\'' && c == '\'')
// 				c = '\0';
// 			else if (line[i] == '\"' && c == '\"')
// 				c = '\0';
// 			if (s == 0 && iswhitespace(line[i]) && c == '\0')
// 			{
// 				arg = ft_realloc(arg, ft_strlen(arg) + 2);
// 				ft_strncat(arg, &line[i], 1);
// 				s = 1;
// 			}
// 			else if (s == 1 && !iswhitespace(line[i]))
// 			{
// 				arg = ft_realloc(arg, ft_strlen(arg) + 2);
// 				ft_strncat(arg, &line[i], 1);
// 				s = 0;
// 			}
// 			else
// 			{
// 				arg = ft_realloc(arg, ft_strlen(arg) + 2);
// 				ft_strncat(arg, &line[i], 1);
// 			}
// 			i++;
// 		}
// 	}
// 	free(line);
// 	return (remove_white_spaces(arg));
// }

char	*expand_input(t_env *env, char *line)
{
	int		i;
	char	c;
	int		s;
	char	*arg;
	int		k;

	i = 0;
	c = '\0';
	arg = ft_strdup("");
	s = 0;
	while (line[i])
	{
		if ((line[i] == '~' && (iswhitespace(line[i + 1])
			|| line[i + 1] == '\0' || line[i + 1] == '/') && c == '\0'))
		{
			if (ft_getenv(env, "HOME"))
				arg = reallocated_str(arg, ft_getenv(env, "HOME"));
			else
			{
				arg = ft_realloc(arg, ft_strlen(arg) + 2);
				ft_strncat(arg, &line[i], 1);
			}
			i++;
		}
		else if (s == 0 && (!c || c == '\"') && line[i] == '$' && (ft_isalpha(line[i + 1])
				|| line[i + 1] == '?' || line[i + 1] == '{'
				|| line[i + 1] == '_'))
		{
			k = 0;
			while (line[k + i + 1] && line[k + i + 1] != '?' && line[k + i + 1] != '{'
				&& (ft_isalnum(line[k + i + 1]) || line[k + i + 1] == '_'))
				k++;
			if (line[k + i + 1] == '{')
				k++;
			if (line[k + i + 1] == '?')
				k++;
			// printf("expand_env_var in\n");
			arg = expand_env_var(env, &line[i + 1], arg, &k);
			// printf("expand_env_var out\n");
			i += k + 1;
		}
		else if (line[i])
		{
			c = double_or_single(line[i], c);
			if (!c && (line[i] == '<' || line[i] == '>'))
				s = 1;
			if (line[i] != '<' && line[i] != '>' && !iswhitespace(line[i]))
				s = 0;
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i], 1);
			i++;
		}
	}
	free(line);
	return (remove_white_spaces(arg));
}
