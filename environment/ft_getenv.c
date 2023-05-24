/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:26 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 13:58:52 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
