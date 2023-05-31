/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/31 01:54:34 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_init_pwd(char *pwd, int stat)
{
	static char *cwd;

	if (pwd == NULL && stat == 1)
		return (cwd);
	if (stat == 0)
	{
		cwd = getcwd(NULL, PATH_MAX + 1);
		if (cwd == NULL)
		{
			printf("shell-init: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n");
			printf("sh: 0: getcwd() failed: No such file or directory\n");
		}
	}
	else if (stat == 1)
	{
		free(cwd);
		cwd = pwd;
	}
	else if (stat == 2)
		return (free(cwd), NULL);
	return (cwd);
}

int	ft_pwd(t_cmd *command)
{
	char	*cwd;

	cwd = shell_init_pwd(NULL, 1);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (0);
	}
	write(command->cmd_out, cwd, ft_strlen(cwd));
	write(command->cmd_out, "\n", 1);
	return (0);
}
