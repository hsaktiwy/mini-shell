/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:24:21 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/10 16:47:13 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_cmd *command, t_env *env)
{
	t_list	*list;

	list = env->l_env;
	sort_env_list(env->l_env);
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

void	get_value(char *key, char *arg, t_env *env, char **value)
{
	char	*equal_p;
	char	*tmp;
	char	*env_value;

	equal_p = ft_strchr(arg, '=');
	if (!equal_p)
		return (*value = NULL, ft_void());
	if (*(equal_p - 1) == '+')
	{
		env_value = ft_getenv(env, key);
		if (*(equal_p + 1))
			tmp = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		else
			tmp = ft_strdup("");
		*value = ft_strjoin(env_value, tmp);
		free(tmp);
	}
	else
	{
		if (*(equal_p + 1))
			*value = ft_substr(equal_p + 1, 0, ft_strlen(equal_p + 1));
		else
			*value = ft_strdup("");
	}
}

void	ft_helper(char *key, char *arg, char **value)
{
	t_env	*env;

	env = g_env_s(NULL);
	get_value(key, arg, env, value);
	ft_setenv(&env, key, *value);
	free(key);
	free(*value);
}

int	ft_export(t_cmd *command)
{
	t_list	*arg_list;
	char	*value;
	char	*key;
	char	*arg;
	char	status;

	status = 0;
	arg_list = command->arg;
	if (command->arg_count == 0)
		print_export(command, g_env_s(NULL));
	while (arg_list)
	{
		arg = ((t_file *)(arg_list->content))->a_file;
		arg_list = arg_list->next;
		key = get_key(arg);
		if (check_key(key))
		{
			free(key);
			print_error2(arg, 1);
			status = 1;
			continue ;
		}
		ft_helper(key, arg, &value);
	}
	return (status);
}
