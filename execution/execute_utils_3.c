/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:37:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/09 21:30:42 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_name_of_signal(int sig)
{
	if (sig == 2)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (sig == 3)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	if (sig == 6)
		ft_putstr_fd("Aborted\n", STDERR_FILENO);
	if (sig == 7)
		ft_putstr_fd("Bus error\n", STDERR_FILENO);
	if (sig == 8)
		ft_putstr_fd("Floating point exception\n", STDERR_FILENO);
	if (sig == 9)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (sig == 10)
		ft_putstr_fd("User-defined signal 1\n", STDERR_FILENO);
	if (sig == 11)
		ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
	if (sig == 12)
		ft_putstr_fd("User-defined signal 2\n", STDERR_FILENO);
	if (sig == 13)
		ft_putstr_fd("Broken pipe\n", STDERR_FILENO);
	if (sig == 14)
		ft_putstr_fd("Alarm clock\n", STDERR_FILENO);
	if (sig == 15)
		ft_putstr_fd("Terminated\n", STDERR_FILENO);
}

void	restore_signals_in_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		if (g_heredoc_executing(-1))
		{
			printf("^C");
			fd = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_cmd_executing(-2);
			g_stdin_fd(fd);
		}
		else if (g_cmd_executing(-1) == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 1;
	}
}

void	script_line(void)
{
	if (g_script_mode(-1))
	{
		write(STDERR_FILENO, "line ", 5);
		ft_putnbr_fd(g_script_mode(-1), STDERR_FILENO);
		write(STDERR_FILENO, ": ", 2);
	}
}

void	before_exiting2(void)
{
	t_list	*tokens;
	t_env	*env;

	tokens = g_token_l(NULL);
	free_tokens(&tokens);
	free(g_input_line(NULL));
	env = g_env_s(NULL);
	ft_free_env(&env);
	rl_clear_history();
	exit(2);
}
