/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/31 16:22:33 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error3(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": error retrieving current directory: ", 38);
	write(STDERR_FILENO, "getcwd: cannot access parent directories: ", 42);
	write(STDERR_FILENO, "No such file or directory\n", 26);
	return (1);
}

char	*shell_init_pwd(char *pwd, int stat)
{
	static char *cwd;

	if (pwd == NULL && stat == 1)
		return (cwd);
	if (stat == 0)
	{
		cwd = getcwd(NULL, PATH_MAX + 1);
		if (cwd == NULL)
			print_error3("shell-init");
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
		return (print_error3("pwd"));
	write(command->cmd_out, cwd, ft_strlen(cwd));
	write(command->cmd_out, "\n", 1);
	return (0);
}
