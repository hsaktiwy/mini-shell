/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:14 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/13 16:08:30 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

char	*join_key_value(char *key, char *value)
{
	char	*res;
	char	*btw;

	btw = str_join(key, "=");
	res = str_join(btw, value);
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
		while(key[k] && env_table[index][j] && env_table[index][j] != '=')
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

void	ft_modifie_key(t_env **env, char *key, char *value, char *key_val)
{
	t_list		*list;
	t_holder	*holder;
	ssize_t		index;

	// Update env list
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
	// Update env table ///////////////////
	index = get_env_index((*env)->env, key);	// get index of env in table
	if (index == -1) // in case env is not found
		return ;
	free((*env)->env[index]);			// free old env
	(*env)->env[index] = key_val;		// add new env (already allocated by join_key_value())
}

char	**ft_realloc_env_table(char **env_table, char *key_val)
{
	char	**strs;
	size_t	size;
	size_t	i;

	size = ft_t_strlen(env_table);
	strs = ft_t_strdup(env_table, size + 1);
	i = 0;
	while(env_table[i])
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
		return (no_mem(), NULL);

	holder->key = ft_strdup(key);
	holder->value = ft_strdup(value);
	return (holder);
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
	key_val = join_key_value(key, value);
	if (old_env == NULL)
	{
		// add env in env_table
		if (value)
			(*env)->env = ft_realloc_env_table((*env)->env, key_val);
		//add env in env_list
		if (key_is_in_list((*env)->l_env, key))	// if the key already exist in the list with a null value
			add_value((*env)->l_env, key, value);
		else
			ft_lstadd_back(&((*env)->l_env), ft_lstnew(ft_lstnewholder(key, value)));
	}
	else
	{	
		//modify existing env
		if (value)
			ft_modifie_key(env, key, value, key_val);
	}
}
