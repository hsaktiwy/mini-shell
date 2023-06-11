/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/11 05:24:29 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_open_fds(t_list *list)
{
	int	fd;

	while (list)
	{
		if (((t_cmd *)(list->content))->cmd_in != 0)
		{
			fd = ((t_cmd *)(list->content))->cmd_in;
			if (close(fd) == -1)
				perror("minishell: close");
		}
		if (((t_cmd *)(list->content))->cmd_out != 1)
		{
			fd = ((t_cmd *)(list->content))->cmd_out;
			if (close(fd) == -1)
				perror("minishell: close");
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

int	ft_forking(t_list *cmd, t_list *list, t_fd *fd, t_execve_params *ep)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		g_exit_status = 1;
		return (1);
	}
	else if (pid == 0)
	{
		restore_signals_in_child();
		dup_stdin_and_stdout(cmd, fd);
		dup_redirections(cmd);
		close_open_fds(list);
		execb2(cmd, list);
		exec_c(ep, g_env_s(NULL));
	}
	wait_4_last_command(cmd, pid);
	return (0);
}

int	execute_2(t_list *cmd, t_list *list, int *get_exit, t_fd *fd)
{
	t_execve_params	ep;

	ft_piping(cmd, fd);
	if (((t_cmd *)(cmd->content))->cmd && !((t_cmd *)(cmd->content))->error)
	{
		ep.path = findcmd(((t_cmd *)(cmd->content))->cmd);
		ep.args = get_args(cmd);
		save_cmd(&ep, g_env_s(NULL));
		if (!ep.path)
			return (close_pipe(cmd, fd), free(ep.args),
				command_not_found(cmd, get_exit), 0);
		if (execb1(cmd, list, get_exit, &ep))
			return (close_pipe(cmd, fd), 0);
		if (ft_forking(cmd, list, fd, &ep) == 1)
			return (g_exit_status = 1, *get_exit = 0, close_pipe(cmd, fd),
				free(ep.path), free(ep.args), 1);
		free(ep.path);
		free(ep.args);
	}
	close_pipe(cmd, fd);
	if ((((t_cmd *)(cmd->content))->error) && !cmd->next)
		return (*get_exit = 0, g_exit_status = 1, 0);
	return (0);
}

void	execute(t_list *list)
{
	t_list	*curr_cmd;
	int		get_exit;
	t_fd	fd;

	if (g_cmd_executing(-1) == -2)
		return (g_exit_status = 1, g_cmd_executing(0), ft_void());
	curr_cmd = list;
	ft_init_fd(&fd, &get_exit);
	while (curr_cmd)
	{
		g_cmd_executing(1);
		fd.old_fd = fd.fd[0];
		if (execute_2(curr_cmd, list, &get_exit, &fd) == 1)
			break ;
		curr_cmd = curr_cmd->next;
	}
	while (wait(NULL) > -1)
		;
	g_cmd_executing(0);
	close_open_fds(list);
	if (get_exit)
		get_exit_status();
}
