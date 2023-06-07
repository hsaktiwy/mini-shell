/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:35:13 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/07 21:04:58 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_key_value(char *key, char *value)
{
	char	*res;
	char	*btw;

	btw = ft_strjoin(key, "=");
	res = ft_strjoin(btw, value);
	free(btw);
	return (res);
}

ssize_t	get_env_index(char **env_table, char *key)
{
	ssize_t	index;
	size_t	j;
	size_t	k;

	index = 0;
	while (env_table[index])
	{
		j = 0;
		k = 0;
		while (key[k] && env_table[index][j] && env_table[index][j] != '=')
		{
			if (key[k] != env_table[index][j])
				break ;
			j++;
			k++;
		}
		if (env_table[index][j] == '=' && key[k] == 0)
			return (index);
		index++;
	}
	return (-1);
}

int	key_is_in_list(t_list *list, char *key)
{
	while (list)
	{
		if (ft_strcmp(((t_holder *)(list->content))->key, key) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
