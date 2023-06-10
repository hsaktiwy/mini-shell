/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:24:11 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/10 19:56:24 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_wildcard(char *input)
{
	int		i;
	char	c;

	c = '\0';
	i = -1;
	while (input[++i])
	{
		c = double_or_single(input[i], c);
		if (!c && input[i] == '*')
			return (1);
	}
	return (0);
}

// ini_s is the initial input (i will create a function that repplace
// trure wildcards with a \n : dfine true(exp : 'test*'* the * that are at 
//the last of the exp is the true wildcard unlick the one attached to test))
// i used t_c to help me keep trap if c change like in this case with out this
//trap : exp (a*'*') result will be (a\n*') while we want (a\n*)
char	*replace_true_wildcards(char *arg)
{
	int		i;
	char	c;
	char	*res;
	char	t_c;

	res = ft_strdup("");
	i = -1;
	c = '\0';
	while (arg[++i])
	{
		t_c = c;
		c = double_or_single(arg[i], c);
		if (!c && arg[i] == '*')
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, "\n", 1);
		}
		else if ((!c || arg[i] != c) && t_c == c)
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &arg[i], 1);
		}
	}
	return (res);
}

char	*iswildcards(char *input, char	*ini_s)
{
	char	*arg;
	char	*tmp;

	tmp = NULL;
	if (input && ini_s && is_there_wildcard(ini_s))
	{
		tmp = replace_true_wildcards(ini_s);
		arg = local_dir(tmp);
		return (free(input), free(tmp), arg);
	}
	if (ini_s)
	{
		tmp = get_token(ini_s);
		if (!tmp)
			tmp = ft_strdup(ini_s);
	}
	return (free(input), tmp);
}
