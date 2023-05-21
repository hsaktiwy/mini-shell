/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:06:50 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/21 17:06:50 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	get_status_put_error(char *arg, size_t arg_count, int *do_exit, int *status)
{
	if (arg_count == 1 && check_arg(arg))
	{
		*status = ft_atoi(arg);
	}
	else if (arg_count > 1 && check_arg(arg))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		*do_exit = 0;
		*status = 1;
	}
	else
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 28);
		*status = 255;
	}
}

int	ft_exit(t_cmd *command, t_list *list)
{
	int				status;
	int				do_exit;
	char			*arg;
	t_list			*g_tokens;
	t_env 			*g_env;

	do_exit = 1;
	status = 0;
	if (ft_lstsize(list) == 1)
		write(2, "exit\n", 5);
	if (command->arg_count != 0)
	{
		arg = ((t_file *)(command->arg->content))->a_file;
		get_status_put_error(arg, command->arg_count, &do_exit, &status);
	}
	if (do_exit)
	{
		if (ft_lstsize(list) == 1)
		{
			g_tokens = g_token_l(NULL);
			free_tokens(&g_tokens);
			ft_lstclear(&list, NULL);
			free(g_input_line(NULL));
			g_env = g_env_s(NULL);
			ft_free_env(&g_env);
			rl_clear_history();
		}
		exit(status);
	}
	return (status);
}
