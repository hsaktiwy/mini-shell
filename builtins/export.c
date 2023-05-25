/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:24:21 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/25 14:40:27 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f(char *key1, char*key2)
{
	if (ft_strcmp(key1, key2) <= 0)
		return (0);
	else
		return (1);
}

t_list	*sort_env_list(t_list *list)
{
	char	*p;
	t_list *head;
	t_list *tmp;

	head = list;
	while (head)
	{
		tmp = head->next;
		while (tmp)
		{
			if (f(((t_holder *)(head->content))->key,
					((t_holder *)(tmp->content))->key))
			{
				p = ((t_holder *)(head->content))->key;
				((t_holder *)(head->content))->key = ((t_holder *)(tmp->content))->key;
				((t_holder *)(tmp->content))->key = p;
				p = ((t_holder *)(head->content))->value;
				((t_holder *)(head->content))->value = ((t_holder *)(tmp->content))->value;
				((t_holder *)(tmp->content))->value = p;
			}
			tmp = tmp->next;
		}
		head = head->next;
	}
	return (list);
}

void	print_export(t_cmd *command)
{
	t_list	*list;

	list = sort_env_list(command->env->l_env);
	while (list)
	{
		if (ft_strcmp(((t_holder *)(list->content))->key, "_") != 0)
		{
			if (((t_holder *)(list->content))->key)
			{
				write(command->cmd_out, "declare -x ", 11);
				write(command->cmd_out, ((t_holder *)(list->content))->key,
					ft_strlen(((t_holder *)(list->content))->key));
			}
			if (((t_holder *)(list->content))->value)
			{
				write(command->cmd_out, "=\"", 2);
				write(command->cmd_out, ((t_holder *)(list->content))->value,
					ft_strlen(((t_holder *)(list->content))->value));
				write(command->cmd_out, "\"", 1);
			}
			write(command->cmd_out, "\n", 1);
		}
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
		if (*(equal_p + 1))
			tmp = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		else
			tmp = ft_strdup("");
		value = ft_strjoin(env_value, tmp);
		free(tmp);
	}
	else
	{
		if (*(equal_p + 1))
			value = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		else
			value = ft_strdup("");
	}
	return (value);
}

int	ft_export(t_cmd *command)
{
	t_list	*arg_list;
	char	*value;
	char	*key;
	char	*arg;

	arg_list = command->arg;
	if (command->arg_count == 0)
		print_export(command);
	while (arg_list)
	{
		arg = ((t_file *)(arg_list->content))->a_file;
		key = get_key(arg);
		if (check_key(key))
		{
			free(key);
			return (print_error2(arg, 1));
		}
		value = get_value(key, arg, command->env);
		ft_setenv(&(command->env), key, value);
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
