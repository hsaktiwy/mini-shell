/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:50:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/03 15:46:20 by aigounad         ###   ########.fr       */
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

void	set_pwd(int *flag, char *oldpwd, t_cmd *cmd, t_env *env)
{
	char	*cwd;
	char	*tmp;

	if (!*flag)
		ft_setenv(&env, "OLDPWD", oldpwd);
	else
		ft_setenv(&env, "OLDPWD", "");
	cwd = getcwd(NULL, PATH_MAX + 1);
	if (cwd != NULL)
	{
		ft_setenv(&env, "PWD", cwd);
		shell_init_pwd(cwd, 1);
		*flag = 0;
	}
	else
	{
		print_error3("cd");
		if (ft_strcmp(((t_file *)(cmd->arg->content))->a_file, "..") == 0)
			tmp = ft_strjoin(shell_init_pwd(NULL, 1), "/..");
		else
			tmp = ft_strjoin(shell_init_pwd(NULL, 1), "/.");
		shell_init_pwd(tmp, 1);
	}
	return ;
}

int	check_prev_dir(t_cmd *cmd, int flag)
{
	DIR	*dir;

	if (cmd->arg_count <= 0)
		return (0);
	if (flag == 0
		&& ft_strcmp(((t_file *)(cmd->arg->content))->a_file, "..") == 0)
	{
		dir = opendir("..");
		if (dir == NULL)
		{
			perror("minishell: cd: ..");
			return (1);
		}
		closedir(dir);
	}
	return (0);
}

int	ft_cd(t_cmd *command)
{
	char		*path;
	char		cwd[PATH_MAX + 1];
	char		*oldpwd;
	static int	flag;

	if (check_prev_dir(command, flag))
		return (1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		flag = 1;
	path = get_path(command, command->env);
	if (!path || !*path)
		return (1);
	if (chdir(path) == -1)
		return (print_error(command->cmd, path, 1), 1);
	if (command->arg_count != 0
		&& ft_strcmp(((t_file *)(command->arg->content))->a_file, "-") == 0)
	{
		oldpwd = ft_getenv(command->env, "OLDPWD");
		if (oldpwd)
			write(command->cmd_out, oldpwd, ft_strlen(oldpwd));
		write(command->cmd_out, "\n", 1);
	}
	return (set_pwd(&flag, cwd, command, g_env_s(NULL)), 0);
}
