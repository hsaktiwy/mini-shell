/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/30 00:58:38 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *command)
{
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	if (cwd == NULL)
	{
		cwd = ft_getenv(command->env, "PWD");
		if (cwd != NULL)
			write(command->cmd_out, &cwd, ft_strlen(cwd));
		write(command->cmd_out, "\n", 1);
		return (0);
	}
	write(command->cmd_out, &cwd, ft_strlen(cwd));
	write(command->cmd_out, "\n", 1);
	free(cwd);
	return (0);
}
