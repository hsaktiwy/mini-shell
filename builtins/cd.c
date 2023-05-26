/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:50:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 15:08:58 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *command, char *str_error, int print_error)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (command)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": ", 2);
	}
	if (print_error)
		perror(str_error);
	else
		write(STDERR_FILENO, str_error, ft_strlen(str_error));
	return (1);
}

char	*get_path(t_cmd *command, t_env *env)
{
	char	*path;

	if (command->arg_count <= 0)
	{
		path = ft_getenv(env, "HOME");
		if (path == NULL)
			print_error(command->cmd, "HOME not set\n", 0);
	}
	else if (ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
	{
		path = ft_getenv(env, "OLDPWD");
		if (path == NULL || !*path)
			print_error(command->cmd, "OLDPWD not set\n", 0);
	}
	else if (ft_strcmp(((t_file *)(command->arg->content))->a_file, "--") == 0)
	{
		path = ft_getenv(env, "HOME");
		if (path == NULL)
			print_error(command->cmd, "HOME not set\n", 0);
	}
	else
		path = ((t_file *)(command->arg->content))->a_file;
	return (path);
}

int	ft_cd(t_cmd *command)
{
	char	*path;
	char	cwd[4096];
	char	*oldpwd;

	getcwd(cwd, 4096);
	path = get_path(command, command->env);
	if (!path || !*path)
		return (1);
	if (chdir(path) != 0)
	{
		print_error(command->cmd, path, 1);
		return (1);
	}
	if (command->arg_count != 0
		&& ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
	{
		oldpwd = ft_getenv(command->env, "OLDPWD");
		write(command->cmd_out, oldpwd, ft_strlen(oldpwd));
		write(command->cmd_out, "\n", 1);
	}
	ft_setenv(&(command->env), "OLDPWD", cwd);
	ft_setenv(&(command->env), "PWD", getcwd(cwd, 4096));
	return (0);
}
