/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:34:45 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/25 14:45:37 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_input_line(char *input)
{
	static char	*g_input;

	if (input == NULL)
		return (g_input);
	g_input = input;
	return (g_input);
}

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

int	g_heredoc_executing(int i)
{
	static int	j;
	
	if (i == -1)
		return (j);
	j = i;
	return (j);
}

int	g_pipe_count(int i)
{
	static	int j;

	if (i == -1)
		return (j);
	j = i;
	return (j);
}

int g_heredoc_count(int	i)
{
	static int	j;

	if (i == 1)
		j++;
	else if (i == 0)
		j = 0;
	return (j);
}
