#include "environement.h"

t_holder	*ft_lstnewholder(char *str)
{
    char		**res;
    t_holder	*holder;

	holder = (t_holder *)malloc(sizeof(t_holder));
	if (!holder)
		return (no_mem(),NULL);
    res = ft_split(str, '=');
	if (str[0])
	{
		holder->key = ft_strdup(res[0]);
		if (str[1])
			holder->value = ft_strdup(res[1]);
		else
			holder->value = ft_strdup("");
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

	i = -1;
	list = NULL;
	while (env[++i])
	{
		holder = ft_lstnewholder(env[i]);
		if (holder)
			ft_lstadd_back(&list, ft_lstnew(holder));
	}
	return (list);
}

t_env	*ft_init_env(char **env)
{
	t_env	*env_l;

	env_l = (t_env *)malloc(sizeof(t_env));
	if (!env_l)
		return (no_mem(), NULL);
	env_l->env = ft_t_strdup(env);
	env_l->l_env = ft_lst_list_holder(env);
	ft_setenv(&env_l, "OLDPWD", NULL);
	return (env_l);
}

// int main(int argc, char **arg, char **env)
// {
// 	t_env *list;

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
// 	return (0);
// }