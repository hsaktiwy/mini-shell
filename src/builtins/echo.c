/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:34:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/17 19:04:34 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_printf(t_cmd *command, t_list *arg_list)
{
	char	*p;

	while (arg_list)
	{
		p = ((t_file *)(arg_list->content))->a_file;
		if (write(command->cmd_out, p, ft_strlen(p)) < 0)
			exit(1);
		if (arg_list->next)
		{
			if (write(command->cmd_out, " ", 1) < 0)
				exit(1);
		}
		arg_list = arg_list->next;
	}
}

int	is_valid_arg(char *arg)
{
	size_t	i;
	int		n;

	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	i = 1;
	n = 0;
	while (arg[i] && arg[i] == 'n')
	{
		i++;
		n++;
	}
	if (arg[i] != 0 || n == 0)
		return (0);
	return (1);
}

int	ft_echo(t_cmd *command)
{
	int	flag;
	t_list	*arg_list;

	flag = 0;
	arg_list = command->arg;
	if (command->arg_count > 0)
	{
		while (arg_list && is_valid_arg(((t_file *)(arg_list->content))->a_file))
		{
			flag = 1;
			arg_list = arg_list->next;
		}
		ft_printf(command, arg_list);
	}
	if (!flag)
	{
		if (write(command->cmd_out, "\n", 1) < 0)
			exit(1);
	}
	return (0);
}
