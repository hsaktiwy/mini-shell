/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:50:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/30 17:30:56 by aigounad         ###   ########.fr       */
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

void	change_env_vars(int flag, char *oldpwd)
{
	(void)oldpwd;
	static char	cwd[PATH_MAX + 1];
	t_env	*env;

	env = g_env_s(NULL);
	if (!flag)
		ft_setenv(&env, "OLDPWD", cwd);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
		ft_setenv(&env, "PWD", cwd);
}

int	handle_special_case(t_cmd *command)
{
    DIR* dir = opendir(((t_file *)(command->arg->content))->a_file);
    if (dir == NULL) {
        perror("minishell: cd: ..");
        return 1;
    }
    closedir(dir);
	return (0);
}

int	ft_cd(t_cmd *command)
{
	char	*path;
	char	cwd[PATH_MAX + 1];
	char	*oldpwd;
	int		flag;
	static	char *tmp;


	if (command->arg_count != 0
		&& ft_strcmp(((t_file *)(command->arg->content))->a_file, "..") == 0)
	{
		if (handle_special_case(command))
		return (0);
	}
	flag = 0;
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		// printf("cd: error retrieving current directory\n");
		flag = 1;
	}
	path = get_path(command, command->env);
	if (!path || !*path)
		return (1);
	if (chdir(path) == -1)
		return (print_error(command->cmd, path, 1), 1);
	/////////////////////////////////////////////////////////////////////
	if (command->arg_count != 0
		&& ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
	{
		oldpwd = ft_getenv(command->env, "OLDPWD");
		if (oldpwd)
			write(command->cmd_out, oldpwd, ft_strlen(oldpwd));
		write(command->cmd_out, "\n", 1);
	}
	//////////////////////////////////////////////////////////////////////
	change_env_vars(flag, cwd);
	return (0);
}
