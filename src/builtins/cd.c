/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:50:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/07 18:45:45 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_error(char *command, char *str_error, int print_error)
{
	write(2, "minishill: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (print_error)
		perror(str_error);
	else
		write(2, str_error, ft_strlen(str_error));
	return (1);
}

char	*get_path(t_cmd *command, char **env)
{
	char *path; (void)env;
	
	if (command->arg_count <= 0)
	{
		path = getenv("HOME");
		if (path == NULL)
			print_error(command->cmd, "HOME not set\n", 0);
	}
	else
	{
		printf("arg == %s\n\n", command->arg->content);
		if (ft_strcmp(command->arg->content, "-") == 0)
		{
			path = getenv("OLDPWD");
			if (path == NULL)
				print_error(command->cmd, "OLDPWD not set\n", 0);
		}
		else if (ft_strcmp(command->arg->content, "--") == 0)
		{
			path = getenv("HOME");
			if (path == NULL)
				print_error(command->cmd, "HOME not set\n", 0);
		}
		else
			path = command->arg->content;
	}
	return (path);
}

int	cd(t_cmd *command, char **env)
{
	char	*path;
	char	cwd[4096];

	if (command->arg_count > 1)
		return (print_error(command->cmd, "too many arguments\n", 0));
	path = get_path(command, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		print_error(command->cmd, path, 1);
	}
	if (ft_strcmp(command->arg->content, "--") == 0)
	{
		getcwd(cwd, 4096);
		printf("%s\n", path);
	}
	return (0);
}
