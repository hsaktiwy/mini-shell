/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:21:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 14:50:03 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
