#include "environement.h"

char	*ft_getenv(t_env *env, char	*key)
{
	t_list		*list;
	t_holder	*holder;

	list = env->l_env;
	while (list)
	{
		holder = list->content;
		if (ft_strcmp(holder->key, key) == 0)
			return (holder->value);
		list = list->next;
	}
	return (NULL);
}
