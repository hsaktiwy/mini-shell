/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:34:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/09 18:01:45 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// int	ft_strcmp(char *str1, char *str2)
// {
// 	int	i;

// 	i = 0;
// 	if (!str1 || !str2)
// 		return (-256);
// 	while (str1[i] && str2[i])
// 	{
// 		if (str1[i] != str2[i])
// 			return (str1[i] - str2[i]);
// 		i++;
// 	}
// 	return (0);
// }

void	ft_printf(t_list *arg_list)
{
	while (arg_list)
	{
		if (printf("%s", ((t_file *)(arg_list->content))->a_file) < 0)
			exit(1);
		if (arg_list->next)
		{
			if (printf(" ") < 0)
				exit(1);
		}
		arg_list = arg_list->next;
	}
}

int	ft_echo(t_cmd *command)
{
	int	flag;
	t_list	*arg_list;

	flag = 0;
	arg_list = command->arg;
	if (command->arg_count > 1)
	{
		if (ft_strcmp(((t_file *)(arg_list->content))->a_file, "-n") == 0)
		{
			flag = 1;
			arg_list = arg_list->next;
		}
		ft_printf(arg_list);
	}
	if (!flag)
	{
		if (printf("\n") < 0)
			exit(1);
	}
	return (0);
}
