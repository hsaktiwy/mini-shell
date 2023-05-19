/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:21:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/19 00:56:40 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_env(t_cmd *command)
{
	char **pp;

	pp = command->env->env;
	if (!pp)
		return;
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
