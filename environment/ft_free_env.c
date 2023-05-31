/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:25:19 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/31 01:31:28 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	t_holder	*holder;

	if (!*list)
		return ;
	free_list(&((*list)->next));
	holder = (*list)->content;
	free(holder->key);
	free(holder->value);
	free(holder);
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
	shell_init_pwd(NULL, 2);
}
