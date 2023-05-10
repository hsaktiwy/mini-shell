/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:50:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/09 20:10:33 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_error(char *command, char *str_error, int print_error)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (print_error)
		perror(str_error);
	else
		write(2, str_error, ft_strlen(str_error));
	return (1);
}

char	*get_path(t_cmd *command, t_env *env)
{
	char *path; (void)env;

	if (command->arg_count <= 0)
	{
		path = ft_getenv(env, "HOME");
		if (path == NULL)
			print_error(command->cmd, "HOME not set\n", 0);
	}
	else
	{
		if (ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
		{
			path = ft_getenv(env, "OLDPWD");
			if (path == NULL)
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
	}
	return (path);
}

int	ft_cd(t_cmd *command, t_env *env)
{
	char	*path;
	char	cwd[4096];

	if (command->arg_count > 1)
		return (print_error(command->cmd, "too many arguments\n", 0));
	getcwd(cwd, 4096);
	path = get_path(command, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		print_error(command->cmd, path, 1);
		return (1);
	}
	//print path in case of "-"
	if ( command->arg_count != 0
			&& ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
		printf("%s\n", ft_getenv(env, "OLDPWD"));
	// update env
	ft_setenv(&env, "OLDPWD", cwd);
	ft_setenv(&env, "PWD", getcwd(cwd, 4096));
	return (0);
}
