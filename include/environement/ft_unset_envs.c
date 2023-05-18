/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_envs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:23:53 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/18 10:27:22 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

static void	del(t_list **list)
{
	free(((t_holder *)((*list)->content))->key);
	free(((t_holder *)((*list)->content))->value);
	free((*list)->content);
	free(*list);
}

void	ft_unset_env_list(t_list **env_l, char *key)
{
	t_list		*head;
	size_t		index;

	if (!env_l || !*env_l)
		return ;
	head = *env_l;
	index = 0;
	while (head)
	{
		if (ft_strcmp(((t_holder *)(head->content))->key, key) == 0)
		{
			ft_lstdelete_index(env_l, index, del);
			return ;
		}
		index++;
		head = head->next;
	}
}

void	ft_unset_env_table(char **env_table, size_t index)
{
	char *tmp = env_table[index];
	while (env_table[index])
	{
		env_table[index] = env_table[index + 1];
		index++;
	}
	free(tmp);
}
