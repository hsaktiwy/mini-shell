/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_function_second.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:56:17 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/03 14:59:00 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pipe_count(int i)
{
	static int	j;

	if (i == -1)
		return (j);
	j = i;
	return (j);
}

int	g_heredoc_count(int i)
{
	static int	j;

	if (i == 1)
		j++;
	else if (i == 0)
		j = 0;
	return (j);
}

int	g_heredo_numb(int i)
{
	static int	j;

	if (i == -1)
		return (j);
	j = i;
	return (j);
}
