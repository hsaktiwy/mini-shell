/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:34:45 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/21 17:48:55 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	g_stdin_fd(int i)
{
	static int	j;
	if (i == -1)
		return (j);
	j = i;
	return (j);
}

t_list *g_token_l(t_list *tokens)
{
	static t_list *g_tokens;
	if (tokens == NULL)
		return (g_tokens);
	else
		g_tokens = tokens;
	return (g_tokens);
}
int	g_cmd_executing(pid_t newpid)
{
	static pid_t oldpid;

	if (newpid != -1)
		oldpid = newpid;
	return (oldpid);
}
