/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/04 19:42:47 by hsaktiwy         ###   ########.fr       */
=======
/*   Updated: 2023/06/05 14:38:39 by hsaktiwy         ###   ########.fr       */
>>>>>>> hsaktiwy
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*add_wildcards_to_input(char *input, char *tmp)
// {
// 	char	*res;
// 	char	**tab;
// 	int		i;

// 	i = -1;
// 	res = input;
// 	if (is_spaced_double_single(tmp))
// 	{
// 		tab = ft_split(tmp, ' ');
// 		while (tab[++i])
// 		{
// 			if (ft_strchr(tab[i], '*'))
// 				res = local_dir(res, tab[i]);
// 			else
// 			{
// 				res = str_join(res, ft_strdup("#"));
// 				res = str_join(res, ft_strdup(tab[i]));
// 			}
// 		}
// 		fre_tab(tab);
// 	}
// 	else
// 		res = local_dir(res, tmp);
// 	return (res);
// }

int	is_there_wildcard(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '*')
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

	if (input && is_there_wildcard(input))
	{
		tmp = replace_true_wildcards(ini_s);
		arg = local_dir(tmp);
		return (free(input), free(tmp), arg);
	}
	else
		return (input);
}
