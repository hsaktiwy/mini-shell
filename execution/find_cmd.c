/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:38:32 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 16:53:43 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*findcmd(char *filename)
{
	char	**paths;
	char	path[4096];
	int		i;

	if (is_builtin(filename)
		|| ft_strchr(filename, '/')
		|| !ft_getenv(g_env_s(NULL), "PATH"))
		return (ft_strdup(filename));
	if (ft_strcmp(filename, ".") == 0
		|| ft_strcmp(filename, "..") == 0
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
