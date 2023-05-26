/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:06 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/26 19:10:14 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	double_single_check(char input, char old_c, int *i, int *v)
{
	if (input == '\'' && old_c == '\0')
	{
		old_c = '\'';
		(*v)++;
		(*i)++;
	}
	else if (input == '\"' && old_c == '\0')
	{
		old_c = '\"';
		(*v)++;
		(*i)++;
	}
	else if (input == '\'' && old_c == '\'')
	{
		old_c = '\0';
		(*v)++;
		(*i)++;
	}
	else if (input == '\"' && old_c == '\"')
	{
		old_c = '\0';
		(*v)++;
		(*i)++;
	}
	return (old_c);
}

char	*get_token(char *str)
{
	int		i;
	char	c;
	char 	*res;
	int		c_change;

	i = 0;
	c_change = 0;
	c = '\0';
	res = NULL;
	surpace_whitesspaces(str, &i);
	while (str[i] && str[i] != '|'
		&& str[i] != '<' && str[i] != '>'
		&& !iswhitespace(str[i]))
	{
		c = double_single_check(str[i], c, &i, &c_change);
		if (str[i] && str[i] != '|'
			&& str[i] != '<' && str[i] != '>'
			&& !iswhitespace(str[i])
			&& c != str[i] && !(c == '\0'
			&& (str[i] == '\'' || str[i] == '\"')))
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &str[i], 1);
			i++;
		}
	}
	if (c_change && !res)
		res = ft_strdup("");
	return (res);
}

t_file	*creat_arg(char *file_name, t_argument_type type)
{
	t_file	*arg;

	arg = (t_file *)malloc(sizeof(t_file));
	if (!arg)
		return (NULL);
	arg->a_file = file_name;
	arg->arg_type = type;
	return (arg);
}

int	check_quotes_validity(char *input)
{
	char	c;
	int		i;

	i = 0;
	c = '\0';
	while (input[i])
	{
		if(input[i] == '\'' && !c)
			c = '\'';
		else if (input[i] == '\'' && c == '\'')
			c = '\0';
		else if (input[i] == '\"' && !c)
			c = '\"';
		else if (input[i] == '\"' && c == '\"')
			c = '\0';
		else if (input[i] == '|' && c == '\0')
			break;
		i++;
	}
	if (!c)
		return (1);
	else
		return (0);
}

t_file	*get_file(t_env *env, char *input, int *index)
{
	t_file	*file;
	int		i;

	file = NULL;
	i = 0;
	i += surpace_whitesspaces(input, index);
	if(!input || !input[i])
	{
		file = creat_arg(NULL, WORD);
		return (file);
	}
	else if (input[i] == '\''
		&& check_quotes_validity(&input[i]))
	{
		(*index)++;
		file = creat_arg(get_single_quote(env, &input[++i], index),SINGLE_QUOTE);
	}else if (input[i] == '\"'
		&& check_quotes_validity(&input[i]))
	{
		(*index)++;
		file = creat_arg(get_double_quote(env, &input[++i], index), DOUBLE_QUOTE);
	}
	else if (check_quotes_validity(&input[i]))
	{
		if(input[i] == '$')
			file = creat_arg(get_simple_arg(env, &input[i], index), VARIABLE);
		else
			file = creat_arg(get_simple_arg(env, &input[i], index), WORD);
	}
	return (file);
}
