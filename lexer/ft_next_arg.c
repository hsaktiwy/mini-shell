/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:06 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 16:45:03 by hsaktiwy         ###   ########.fr       */
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
	char	*res;
	int		c_change;
	int		t_c;

	i = 0;
	c_change = 0;
	c = '\0';
	res = NULL;
	surpace_whitesspaces(str, &i);
	while (cond_get_token_one(str[i], c))
	{
		t_c = c;
		c = double_single_check(str[i], c, &i, &c_change);
		if (cond_get_token_sec(str[i], t_c, c))
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

t_file	*creat_arg(char *file_name)
{
	t_file	*arg;

	arg = (t_file *)malloc(sizeof(t_file));
	if (!arg)
		return (NULL);
	arg->a_file = file_name;
	return (arg);
}

int	input_arg_size(char *str)
{
	int		i;
	char	c;

	c = '\0';
	i = 0;
	while (str[i] && ((!c && !iswhitespace(str[i]) && str[i] != '|'
				&& str[i] != '<' && str[i] != '>') || c))
	{
		c = double_or_single(str[i], c);
		i++;
	}
	return (i);
}

t_file	*get_file(t_env *env, char *input, int *index)
{
	t_file	*file;
	char	*tmp;
	char	*r;

	file = NULL;
	surpace_whitesspaces(&input[*index], index);
	r = get_initial_token(&input[*index]);
	if (r && *r)
		r = expand_input(env, r);
	tmp = get_token(&input[*index]);
	*index += input_arg_size(&input[*index]);
	if (!tmp)
	{
		file = creat_arg(NULL);
		return (free(r), file);
	}
	else
		file = creat_arg(tmp);
	if (file)
		file->a_file = iswildcards(file->a_file, r);
	return (free(r), file);
}
