/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:59:30 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/11 17:19:56 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		if (close(fd->fd[1]) == -1)
			perror("minishell: close");
	}
	if (fd->old_fd != -1)
	{
		if (close(fd->old_fd) == -1)
			perror("minishell: close");
	}
}

void	wait_4_last_command(t_list *cmd, pid_t pid)
{
	if (pid == -1)
		return ;
	if (!(cmd->next))
	{
		if (waitpid(pid, &g_exit_status, 0) == -1)
			perror("minishell: waitpid");
	}
}

void	command_not_found(t_list *cmd, int *get_exit)
{
	char	*p;
	char	*error1;
	char	*error2;

	write(STDERR_FILENO, "minishell: ", 11);
	script_line();
	p = ((t_cmd *)(cmd->content))->cmd;
	if (ft_strcmp(p, ".") == 0)
	{
		error1 = ".: filename argument required\n";
		error2 = ".: usage: . filename [arguments]\n";
		write(STDERR_FILENO, error1, 30);
		write(STDERR_FILENO, error2, 33);
		g_exit_status = 2;
		*get_exit = 0;
		return ;
	}
	write(STDERR_FILENO, p, ft_strlen(p));
	write(STDERR_FILENO, ": command not found\n", 20);
	*get_exit = 0;
	g_exit_status = 127;
}
