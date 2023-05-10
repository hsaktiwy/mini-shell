/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:06 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 18:35:11 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

	file = NULL;
	if(!input)
	{
		file = creat_arg(ft_strdup("\0"), WORD);
		return (file);
	}
	else if (input[0] == '\''
		&& check_quotes_validity(input))
	{
		(*index)++;
		file = creat_arg(get_single_quote(env, &input[(*index)], index),SINGLE_QUOTE);
	}else if (input[0] == '\"'
		&& check_quotes_validity(input))
	{
		(*index)++;
		file = creat_arg(get_double_quote(env, &input[(*index)], index), DOUBLE_QUOTE);
	}
	else if (check_quotes_validity(input))
	{
		if(input[0] == '$')
			file = creat_arg(get_simple_arg(env, input, index), VARIABLE);
		else
			file = creat_arg(get_simple_arg(env, input, index), WORD);
	}
	return (file);
}
