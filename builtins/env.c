/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:21:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/10 16:48:21 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_cmd *command, t_env *env)
{
	char	**pp;

	pp = env->env;
	if (!pp)
		return ;
	while (*pp)
	{
		write(command->cmd_out, *pp, ft_strlen(*pp));
		write(command->cmd_out, "\n", 1);
		pp++;
	}
}

int	ft_env(t_cmd *command)
{
	if (command->arg_count > 0)
		return (0);
	print_env(command, g_env_s(NULL));
	return (0);
}
