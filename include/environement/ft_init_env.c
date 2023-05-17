/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/17 15:49:56 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

static t_holder	*ft_lstnewholder(char *key_val, char *pt_equal)
{
    // char		**res;
    t_holder	*holder;

	holder = (t_holder *)malloc(sizeof(t_holder));
	if (!holder)
		return (no_mem(), NULL);
	if (key_val)
	{
		holder->key = ft_substr(key_val, 0,pt_equal - key_val);
		if (!pt_equal)
			holder->value = NULL;
		else
			holder->value = ft_substr(key_val, pt_equal - key_val + 1, ft_strlen(pt_equal + 1));
		return (holder);
	}
	else
		return (free(holder), holder = NULL, NULL);
}

t_list	*ft_lst_list_holder(char **env)
{
	t_list		*list;
	int			i;
	t_holder	*holder;
	char 		*pt_equal;

	i = -1;
	list = NULL;
	while (env[++i])
	{
		pt_equal = ft_strchr(env[i],'=');
		holder = ft_lstnewholder(env[i], pt_equal);
		if (holder)
			ft_lstadd_back(&list, ft_lstnew(holder));
	}
	return (list);
}

t_env	*ft_init_env(char **env)
{
	t_env	*env_l;
	size_t	size;

	env_l = (t_env *)malloc(sizeof(t_env));
	if (!env_l)
		return (no_mem(), NULL);
	size = ft_t_strlen(env);
	env_l->env = ft_t_strdup(env, size);

	env_l->l_env = ft_lst_list_holder(env);
	ft_setenv(&env_l, "OLDPWD", NULL);
	return (env_l);
	
}

// void leak_func()
// {
// 	system("leaks a.out");
// }

// int main(int argc, char **arg, char **env)
// {
// 	t_env *list;
// 	atexit(leak_func);
// 	list = ft_init_env(env);
// 	if (list)
// 	{
// 		int i;

// 		i = -1;
// 		while(list->env[++i])
// 			printf("%s\n", list->env[i]);
// 		t_list *linked = list->l_env;
// 		t_holder *holder;
// 		while (linked)
// 		{
// 			holder = linked->content;
// 			printf("Key = %s : Value = %s\n", holder->key, holder->value);
// 			linked = linked->next;
// 		}
// 		printf("\n\n\n");
// 		printf("res of getenv PATH: %s\n", ft_getenv(list, "PATH"));
// 		printf("res of getenv a: %s\n", ft_getenv(list, "a"));
// 		ft_setenv(&list, "a", "HAHAHA");
// 		printf("res of setenv a: %s\n", ft_getenv(list, "a"));
		
// 	}
// 	ft_free_env(&list);
// 	return (0);
// }
