/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_functions_second.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:56:17 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 16:48:22 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	g_script_mode(int stat)
{
	static int	i;

	if (stat == -1)
		return (i);
	if (stat == 0)
		i = 0;
	else
		i += stat;
	return (i);
}
