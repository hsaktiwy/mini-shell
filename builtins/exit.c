/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:06:50 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 14:51:28 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi2(const char *str)
{
	long double			r;
	int					sign;

	r = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if ((r * sign > LONG_MAX) || (r * sign < LONG_MIN))
			return (-1);
	return (0);
}

static int	check_arg(char *arg)
{
	int	n;

	if (!arg)
		return (0);
	n = ft_atoi2(arg);
	if (n == -1)
		return (0);
	if (arg[0] == '+' || arg[0] == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	before_exiting(t_list *list)
{
	t_list			*tokens;
	t_env 			*env;
	
	if (ft_lstsize(list) == 1)
	{
		tokens = g_token_l(NULL);
		//close_open_fds(list);
		free_tokens(&tokens);
		ft_lstclear(&list, NULL);
		free(g_input_line(NULL));
		env = g_env_s(NULL);
		ft_free_env(&env);
		rl_clear_history();
	}
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
		before_exiting(list);
		exit(status);
	}
	return (status);
}
