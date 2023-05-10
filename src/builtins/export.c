/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:24:21 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/10 22:08:01 by aigounad         ###   ########.fr       */
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
			write(command->cmd_out, ((t_holder *)(list->content))->value,
				ft_strlen(((t_holder *)(list->content))->value));
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

int	check_key(char *key)
{
	size_t	i;

	if (key && *key && !(key[0] >= 'a' && key[0] <= 'z') &&
			!(key[0] >= 'a' && key[0] <= 'z') && key[0] != '_')
		return (1);
	i = 1;
	while(key[i])
	{
		if ((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'a' && key[0] <= 'z') ||
				(key[0] >= '0' && key[0] <= '9') || key[0] == '_')
			i++;
		else
			return (1);
	}
	return (0);
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
		printf(">>>>IM INN\n");
		env_value = ft_getenv(env, key);
		printf(">>>>env_value = [%s]\n", env_value);
		tmp = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		value = str_join(env_value, tmp);
		// free(tmp);
	}
	else
		value = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
	return (value);
}

static int print_error(char *identifier)
{
	write(2, "bash: export: `", 16);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
	return (1);
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
			printf(">>>> KEY = [%s]\n", key);
		if (check_key(key))
		{
			// free(key);
			return (print_error(arg));
		}
		value = get_value(key, arg, env);
			printf(">>>> VALUE = [%s]\n", value);

		// if (!value)
		// {
		// 	free(key);
		// 	return (1);
		// }
		ft_setenv(&env, key, value);
		// ft_setenv should handle if value is NULL and just adds the key without a value
		// free(key);
		// free(value);
		arg_list = arg_list->next;
	}
	return (0);
}
