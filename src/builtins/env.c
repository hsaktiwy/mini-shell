/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:21:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/17 23:02:08 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_env(t_cmd *command)
{
	char **pp;

	pp = command->env->env;

	while (*pp)
	{
		write(command->cmd_out, *pp, ft_strlen(*pp));
		write(command->cmd_out, "\n", 1);
		pp++;
	}
}

int	ft_env(t_cmd *command)
{
	print_env(command);
	return (0);
}
