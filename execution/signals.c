/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:37:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 16:17:24 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_name_of_signal2(int sig)
{
	(void)sig;
}

void	get_name_of_signal(int sig)
{
	if (sig == 2)
		printf("\n");
	if (sig == 3)
		printf("Quit: 3\n");
	if (sig == 6)
		printf("Aborted\n");
	if (sig == 7)
		printf("Bus error\n");
	if (sig == 8)
		printf("Floating point exception\n");
	if (sig == 9)
		printf("\n");
	if (sig == 10)
		printf("User-defined signal 1\n");
	if (sig == 11)
		printf("Segmentation fault: 11\n");
	if (sig == 12)
		printf("User-defined signal 2\n");
	if (sig == 13)
		printf("Broken pipe\n");
	if (sig == 14)
		printf("Alarm clock\n");
	if (sig == 15)
		printf("Terminated\n");
	get_name_of_signal2(sig);
}
