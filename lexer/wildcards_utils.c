/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:07:39 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 20:32:44 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exp_edge(char	**points, char *string, char *exp, int i)
{
	int		corr;
	char	*tmp;

	corr = 1;
	if (!points[i] && exp[0] != '\n')
	{
		tmp = ft_strstr(string, points[0]);
		if (string < tmp)
			corr = 0;
	}
	if (!points[i] && !isendwith(exp) && corr)
	{
		tmp = string;
		while (ft_strstr(&tmp[1], points[i - 1]))
			tmp = ft_strstr(&tmp[1], points[i - 1]);
		tmp = &tmp[ft_strlen(points[i - 1])];
		if (*tmp)
			corr = 0;
	}
	return (corr);
}

int	ft_regx(char *string, char *exp)
{
	char	**points;
	char	*tmp;
	int		i;
	int		corr;

	corr = 1;
	tmp = string;
	points = ft_split(exp, '\n');
	i = -1;
	while (tmp && points[++i] && *tmp)
	{
		tmp = ft_strstr(tmp, points[i]);
		if (tmp)
			tmp = tmp + ft_strlen(points[i]);
	}
	if (!tmp || (!*tmp && points[i]))
		return (fre_tab(points), 0);
	corr = check_exp_edge(points, string, exp, i);
	return (fre_tab(points), corr);
}

char	*add_matchs(struct dirent *entry, char *arg, char	*tmp, int *i)
{
	char	*res;

	res = arg;
	if (entry)
	{
		if (entry->d_name[0] != '.' || tmp[0] == '.')
		{
			if (ft_regx(entry->d_name, tmp))
			{
				res = str_join(res, ft_strdup("\n"));
				res = str_join(res, ft_strdup(entry->d_name));
				(*i)++;
			}
		}
	}
	return (res);
}

char	*local_dir(char *tmp)
{
	char			*res;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	res = ft_strdup("");
	dir = opendir(".");
	if (dir)
	{
		entry = readdir(dir);
		while (entry)
		{	
			res = add_matchs(entry, res, tmp, &i);
			entry = readdir(dir);
		}
		closedir(dir);
	}
	if (i == 0)
	{
		ft_replace(tmp, '\n', '*');
		res = str_join(res, ft_strdup(tmp));
	}
	return (res);
}

int	is_spaced_double_single(char *str)
{
	int		i;
	char	c;

	c = '\0';
	i = -1;
	while (str[++i])
	{
		if (c == '\0' && iswhitespace(str[i]))
			return (1);
		else if (str[i] == '\'' || str[i] == '\"')
			c = double_or_single(str[i], c);
	}
	return (0);
}
