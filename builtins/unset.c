/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:21:36 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/06 21:26:32 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *command)
{
	ssize_t	index;
	t_list	*arg_list;
	char	*arg;
	int		status;

	status = 0;
	arg_list = command->arg;
	while (arg_list)
	{
		arg = ((t_file *)(arg_list->content))->a_file;
		if (check_key(arg))
		{
			print_error2(arg, 2);
			arg_list = arg_list->next;
			status = 1;
			continue ;
		}
		index = get_env_index(command->env->env, arg);
		ft_unset_env_list(&(command->env->l_env), arg);
		if (index != -1)
			ft_unset_env_table(command->env->env, index);
		arg_list = arg_list->next;
	}
	return (status);
}
