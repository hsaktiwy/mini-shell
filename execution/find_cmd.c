/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:38:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/01 18:54:46 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd(t_fd *fd, int *get_exit)
{
	*get_exit = 1;
	fd->fd[0] = -1;
	fd->fd[1] = -1;
}

static void	free_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}

void	append_filename(char *filename, char *path, char *des)
{
	int		j;
	int		k;

	j = -1;
	while (path[++j])
		des[j] = path[j];
	if (des[j - 1] != '/')
		des[j++] = '/';
	k = 0;
	while (filename[k])
		des[j++] = filename[k++];
	des[j] = 0;
}

int	is_a_directory(char *filename)
{
	struct stat	file_info;

	if (stat(filename, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
			return (1);
		else if (S_ISREG(file_info.st_mode))
			return (2);
	}
	else
	{
		return (-1);
		perror("minishell: stat");
	}
	return (0);
}

char	*findcmd(char *filename)
{
	char	**paths;
	char	path[4096];
	int		i;

	if (is_builtin(filename) || ft_strchr(filename, '/')
		|| !ft_getenv(g_env_s(NULL), "PATH"))
		return (ft_strdup(filename));
	if (ft_strcmp(filename, ".") == 0 || (ft_strcmp(filename, "..") == 0)
		|| !*filename)
		return (NULL);
	paths = ft_split(ft_getenv(g_env_s(NULL), "PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		if (!*(paths[i]))
			continue ;
		append_filename(filename, paths[i], path);
		if (access(path, 0) == 0)
			return (free_tab(paths), ft_strdup(path));
	}
	free_tab(paths);
	return (NULL);
}
