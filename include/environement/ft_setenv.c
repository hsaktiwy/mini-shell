#include "environement.h"

char	*join_key_value(char *key, char *value)
{
	char	*res;
	char	*btw;

	btw = ft_strjoin(key, "=");
	res = ft_strjoin(btw, value);
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

void	ft_setenv(t_env **env, char *key, char *value)
{
	char	*v;
	char	*tmp;	

	v = ft_getenv(*env, key);
	if (v == NULL)
	{
		tmp = join_key_value(key, value);
		ft_lstadd_back(&((*env)->l_env), ft_lstnew(ft_lstnewholder(tmp)));
		free(tmp);
	}
	else
	{
		ft_modifie_key(env, key, value);
	}
}
