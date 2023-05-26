/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:14 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 13:45:06 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_modifie_key(t_env **env, char *key, char *value, char *key_val)
{
	t_list		*list;
	t_holder	*holder;
	ssize_t		index;

	list = (*env)->l_env;
	while (list)
	{
		holder = list->content;
		if (ft_strcmp(holder->key, key) == 0)
		{
			free(holder->value);
			holder->value = ft_strdup(value);
			break ;
		}
		list = list->next;
	}
	index = get_env_index((*env)->env, key);
	if (index == -1)
		return ;
	free((*env)->env[index]);
	(*env)->env[index] = key_val;
}

char	**ft_realloc_env_table(char **env_table, char *key_val)
{
	char	**strs;
	size_t	size;
	size_t	i;

	size = ft_t_strlen(env_table);
	strs = ft_t_strdup(env_table, size + 1);
	i = 0;
	while (env_table[i])
	{
		free(env_table[i++]);
	}
	free(env_table);
	strs[size] = key_val;
	return (strs);
}

static t_holder	*ft_lstnewholder(char *key, char *value)
{
	t_holder	*holder;

	holder = (t_holder *)malloc(sizeof(t_holder));
	if (!holder)
		return (perror("malloc"), NULL);
	holder->key = ft_strdup(key);
	holder->value = ft_strdup(value);
	return (holder);
}

void	add_value(t_list *list, char *key, char *value)
{
	while (list)
	{
		if (ft_strcmp(((t_holder *)(list->content))->key, key) == 0)
		{
			((t_holder *)(list->content))->value = ft_strdup(value);
			break ;
		}
		list = list->next;
	}
}

void	ft_setenv(t_env **env, char *key, char *value)
{
	char	*old_env;
	char	*key_val;

	old_env = ft_getenv(*env, key);
	if (value)
		key_val = join_key_value(key, value);
	if (old_env == NULL)
	{
		if (value)
			(*env)->env = ft_realloc_env_table((*env)->env, key_val);
		if (key_is_in_list((*env)->l_env, key))
			add_value((*env)->l_env, key, value);
		else
			ft_lstadd_back(&((*env)->l_env),
				ft_lstnew(ft_lstnewholder(key, value)));
	}
	else
	{	
		if (value)
			ft_modifie_key(env, key, value, key_val);
	}
}
