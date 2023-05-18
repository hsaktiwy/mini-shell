/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:25:19 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/18 10:37:12 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

void	free_list(t_list **list)
{
	t_holder *holder;

	if (!*list)
		return;
	free_list(&((*list)->next));
	holder = (*list)->content;

	// free holder node content
	free(holder->key);
	free(holder->value);
	// free holder
	free(holder);
	// free list
	free(*list);
}

void	ft_free_env(t_env **env_t)
{
	int			i;

	i = -1;
	if ((*env_t))
	{
		if ((*env_t)->env)
		{
			while ((*env_t)->env[++i])
				free((*env_t)->env[i]);
			free((*env_t)->env);
		}
		free_list(&(*env_t)->l_env);
	}
	free(*env_t);
}