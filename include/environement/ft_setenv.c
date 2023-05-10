/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:14 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/10 18:05:08 by aigounad         ###   ########.fr       */
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

void	ft_modifie_key(t_env **env, char *key, char *value)
{
	t_list		*list;
	t_holder	*holder;

	list = (*env)->l_env;
	while (list)
	{
		holder = list->content;
		if (ft_strcmp(holder->key, key) == 0)
		{
			free(holder->value);
			holder->value = ft_strdup(value); 
			return ;
		}
		list = list->next;
	}
}

char	**ft_realloc_env_table(char **env_table, char *key_val)
{
	char	**strs;
	size_t	size;

	size = ft_t_strlen(env_table);
	strs = ft_t_strdup(env_table, size + 1);
	free(env_table);
	strs[size] = key_val;
	return (strs);
}

void	ft_setenv(t_env **env, char *key, char *value)
{
	(void)env;
	(void)key;
	(void)value;
	char	*v;
	char	*key_val;	

	v = ft_getenv(*env, key);
	if (v == NULL)
	{
		key_val = join_key_value(key, value);
		// add env in env_table
		if (value)
			(*env)->env = ft_realloc_env_table((*env)->env, key_val);
		//add env in env_list
		ft_lstadd_back(&((*env)->l_env), ft_lstnew(ft_lstnewholder(key, value)));
		// free(tmp);
	}
	else
	{	
		//modify existing env
		ft_modifie_key(env, key, value);
	}
}
