/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/30 15:24:22 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *command)
{
	char	cwd[PATH_MAX + 1];
	// char	*p;

	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		// p = ft_getenv(command->env, "PWD");
		// if (p != NULL)
		// 	write(command->cmd_out, &p, ft_strlen(p));
		// write(command->cmd_out, "\n", 1);
		return (0);
	}
	write(command->cmd_out, &cwd, ft_strlen(cwd));
	write(command->cmd_out, "\n", 1);
	return (0);
}
