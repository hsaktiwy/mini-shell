/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:24:21 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/11 15:57:10 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_cmd *command, t_env *env)
{
	t_list *list = env->l_env;
	while (list)
	{
		if (((t_holder *)(list->content))->key)
		{
			write(command->cmd_out, "declare -x ", 12);
			write(command->cmd_out, ((t_holder *)(list->content))->key,
				ft_strlen(((t_holder *)(list->content))->key));
		}
		if (((t_holder *)(list->content))->value)
		{
			write(command->cmd_out, "=", 1);
			write(command->cmd_out, "\"", 1);
			write(command->cmd_out, ((t_holder *)(list->content))->value,
				ft_strlen(((t_holder *)(list->content))->value));
			write(command->cmd_out, "\"", 1);
		}
		write(command->cmd_out, "\n", 1);
		list = list->next;
	}
}

char	*get_key(char *arg)
{
	char	*tmp;
	char	*key;

	tmp = ft_strchr(arg, '=');
	if (!tmp)
		key = ft_strdup(arg);
	else if (tmp == arg)
		key = NULL;
	else if (*(tmp - 1) == '+')
	{
		key = ft_substr(arg, 0, tmp - arg - 1);
		if (key && !*key)
			key = NULL;
	}
	else
		key = ft_substr(arg, 0, tmp - arg);
	return (key);
}

char	*get_value(char *key, char *arg, t_env *env)
{
	char	*value;
	char	*equal_p;
	char	*tmp;
	char	*env_value;

	equal_p = ft_strchr(arg, '=');
	if (!equal_p)
		return (NULL);
	if (*(equal_p - 1) == '+')
	{
		env_value = ft_getenv(env, key);
		printf(">>>>env_value = [%s]\n", env_value);
		tmp = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		value = str_join(env_value, tmp);
		free(tmp);
	}
	else
		value = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
	return (value);
}

int	ft_export(t_cmd *command, t_env *env)
{
	t_list	*arg_list;
	char	*value;
	char	*key;
	char	*arg;

	arg_list = command->arg;
	if (command->arg_count == 0)
		print_export(command, env);
	while (arg_list)
	{
		arg = ((t_file *)(arg_list->content))->a_file;
		key = get_key(arg);
		if (check_key(key))
		{
			free(key);
			return (print_error2(arg));
		}
		value = get_value(key, arg, env);
		ft_setenv(&env, key, value);
		free(key);
		free(value);
		arg_list = arg_list->next;
	}
	return (0);
}

// void	fun()
// {
// 	system("leaks a.out");
// }
// // check leaks
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
// 	((t_file *)(command.arg->content))->a_file = "HOME+=value";
// 	command.arg->next = NULL;
// 	env_list = ft_init_env(env);

// 	ft_export(&command, env_list);
// 	print_export(&command, env_list);
	
// 	free(argg);
// 	free(list);
// 	ft_free_env(&env_list);
// }
