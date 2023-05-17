/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:21:36 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/17 23:03:54 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int	ft_unset(t_cmd *command)
{
	ssize_t	index;
	t_list	*arg_list;
	char	*arg;

	arg_list = command->arg;
	while(arg_list)
	{
		arg = ((t_file *)(arg_list->content))->a_file;
		if (check_key(arg))
		{
			print_error2(arg);
			arg_list = arg_list->next;
			continue ;
		}
		index = get_env_index(command->env->env, arg);
		if (index == -1)
		{
			arg_list = arg_list->next;
			continue ;
		}
		ft_unset_env_list(&(command->env->l_env), arg);
		ft_unset_env_table(command->env->env, index);
		arg_list = arg_list->next;
	}
	return (0);
}

// void	fun()
// {
// 	system("leaks a.out");
// }
// // check leaks
// void	print_export(t_cmd *command, t_env *env);
// void	print_env(t_cmd *command, t_env *env);

// int main(int ac, char **av, char **env)
// {
// 	t_env *env_list;
// 	t_cmd command;

// 	t_file	*argg = malloc(sizeof(t_file));
// 	t_list	*list = malloc(sizeof(t_list));

// 	atexit(fun);
// 	command.arg_count = 1;
// 	command.arg = list;
// 	command.arg->content = argg;
// 	command.cmd_out = 1;
// 	command.cmd_in = 0;
// 	((t_file *)(command.arg->content))->a_file = "HOME+=value";
// 	command.arg->next = NULL;
// 	env_list = ft_init_env(env);

// 	ft_unset_env_table(env_list->env, atoi(av[1]));
// 	print_env(&command, env_list);
	
// 	free(argg);
// 	free(list);
// 	ft_free_env(&env_list);
// }