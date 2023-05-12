/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:06:50 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/12 11:37:31 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	ft_exit(t_cmd *command, t_env *env)
{
	(void)env;
	unsigned char	status;
	int				exit;
	char			*arg;

	exit = 1;
	status = 0;
	//if (number of commands is one)
	// write(2, "exit\n", 6);
	if (command->arg_count != 0)
	{
		arg = ((t_file *)(command->arg->content))->a_file;
		if (command->arg_count == 1 && check_arg(arg))
		{
			status = ft_atoi(arg);
		}
		else if (command->arg_count > 1 && check_arg(arg))
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			exit = 0;
		}
		else
		{
			write(2, "minishell: exit: ", 18);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 29);
			status = 255;
		}
	}
	// return (status);
	if (exit)
		exit();
}
