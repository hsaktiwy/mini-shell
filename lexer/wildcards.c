/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
/*   Updated: 2023/06/03 15:30:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_wildcards_to_input(char *input, char *tmp)
{
	char	*res;
	char	**tab;
	int		i;

	i = -1;
	res = input;
	if (is_spaced_double_single(tmp))
	{
		tab = ft_split(tmp, ' ');
		while (tab[++i])
		{
			if (ft_strchr(tab[i], '*'))
				res = local_dir(res, tab[i]);
			else
			{
				res = str_join(res, ft_strdup("#"));
				res = str_join(res, ft_strdup(tab[i]));
			}
		}
		fre_tab(tab);
	}
	else
		res = local_dir(res, tmp);
	return (res);
}

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

char	*iswildcards(char *input, t_argument_type type)
{
	char	*arg;
	char	*tmp;

	arg = ft_strdup("");
	tmp = ft_strtrim(input, " ");
	if (is_there_wildcard(input))
	{
		if (type == VARIABLE)
			arg = add_wildcards_to_input(arg, tmp);
		else
			arg = local_dir(arg, tmp);
		return (free(input), free(tmp), arg);
	}
	else
		return (free(tmp), free(arg), input);
}
