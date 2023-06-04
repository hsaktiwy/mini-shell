/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_second_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:09:25 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/04 19:20:25 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fre_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}

int	isendwith(char *string)
{
	int	i;

	if (string)
	{
		i = ft_strlen(string);
		if (string[i - 1] == '\n')
			return (1);
	}
	return (0);
}

char	double_or_single(char input, char old_c)
{
	if (input == '\'' && old_c == '\0')
		old_c = '\'';
	else if (input == '\"' && old_c == '\0')
		old_c = '\"';
	else if (input == old_c)
		old_c = '\0';
	return (old_c);
}
