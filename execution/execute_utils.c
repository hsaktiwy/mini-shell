/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:59:30 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 16:12:29 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}

void	save_cmd(t_execve_params *ep, t_env *env)
{
	char	**args;

	if (!ep->args || !*(ep->args))
		ft_setenv(&env, "_", ep->path);
	else
	{
		args = ep->args;
		while (*args)
		{
			if (!*(args + 1))
				ft_setenv(&env, "_", *args);
			args++;
		}
	}
}

void	close_pipe(t_list *cmd, t_fd *fd)
{
	if (cmd->next)
		if (close(fd->fd[1]) == -1)
			perror("close");
	if (fd->old_fd > 0)
		if (close(fd->old_fd) == -1)
			perror("close");
}

void	wait_4_last_command(t_list *cmd, pid_t pid)
{
	if (!(cmd->next))
		if (waitpid(pid, &g_exit_status, 0) == -1)
			perror("waitpid");
}

void	command_not_found(t_list *cmd, int *get_exit)
{
	char	*p;

	p = ((t_cmd *)((t_token *)(cmd->content))->value)->cmd;
	if (write(2, "minishell: ", 11) == -1
		|| write(2, p, ft_strlen(p)) == -1
		|| write(2, ": command not found\n", 20) == -1)
		perror("write");
	*get_exit = 0;
	g_exit_status = 127;
}
