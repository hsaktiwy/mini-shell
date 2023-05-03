/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:34:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/01 19:19:13 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-256);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	ft_printf(int start, int end, char	**argv)
{
	while (start < end)
	{
		if (printf("%s", argv[start]) < 0)
			exit(1);
		if (start != end - 1)
		{
			if (printf(" ") < 0)
				exit(1);
		}
		start++;
	}
}

int	echo(int argc, char **argv)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		ft_printf(i, argc, argv);
	}
	if (!flag)
	{
		if (printf("\n") < 0)
			exit(1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	echo(argc, argv);
	return (0);
}