/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 12:16:37 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_open_fds(t_list *list)
{
	int	fd;

	while (list)
	{
		if (((t_cmd *)(((t_token *)(list->content))->value))->cmd_in != 0)
		{
			fd = ((t_cmd *)(((t_token *)(list->content))->value))->cmd_in;
			if (close(fd) == -1)
				perror("close");
		}
		if (((t_cmd *)(((t_token *)(list->content))->value))->cmd_out != 1)
		{
			fd = ((t_cmd *)(((t_token *)(list->content))->value))->cmd_out;
			if (close(fd) == -1)
				perror("close");
		}
		list = list->next;
	}
}

void	get_exit_status(void)
{
	int	sig;

	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		sig = WTERMSIG(g_exit_status);
		g_exit_status = sig + 128;
		get_name_of_signal(sig);
	}
}

void	ft_forking(t_list *cmd, t_list *list, t_fd *fd, t_execve_params *ep)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		restore_signals_in_child();
		dup_stdin_and_stdout(cmd, fd);
		dup_redirections(cmd);
		execb2(cmd, list);
		close_open_fds(list);
		exec_c(ep, g_env_s(NULL));
	}
	wait_4_last_command(cmd, pid);
}

void	execute_2(t_list *cmd, t_list *list, int *get_exit, t_fd *fd)
{
	t_execve_params	ep;

	ft_piping(cmd, fd);
	if (((t_cmd *)(((t_token *)(cmd->content))->value))->cmd
		&& !(((t_cmd *)(((t_token *)(cmd->content))->value))->error))
	{
		ep.path = findcmd(((t_cmd *)((t_token *)(cmd->content))->value)->cmd);
		ep.args = get_args(cmd);
		save_cmd(&ep, g_env_s(NULL));
		if (!ep.path)
			return (free(ep.args), command_not_found(cmd, get_exit));
		if (execb1(cmd, list, get_exit, &ep))
			return ;
		ft_forking(cmd, list, fd, &ep);
		free(ep.path);
		free(ep.args);
	}
	close_pipe(cmd, fd);
}

void	execute(t_list *list)
{
	t_list	*curr_cmd;
	int		get_exit;
	t_fd	fd;

	curr_cmd = list;
	get_exit = 1;
	fd.fd[0] = -1;
	fd.fd[1] = -1;
	g_exit_status = 0;
	while (curr_cmd)
	{
		g_cmd_executing(1);
		fd.old_fd = fd.fd[0];
		execute_2(curr_cmd, list, &get_exit, &fd);
		curr_cmd = curr_cmd->next;
	}
	while (wait(NULL) > -1)
		;
	g_cmd_executing(0);
	close_open_fds(list);
	if (get_exit)
		get_exit_status();
	ft_lstclear(&list, NULL);
}
