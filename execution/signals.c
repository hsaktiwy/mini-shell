/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:37:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 14:11:21 by aigounad         ###   ########.fr       */
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
