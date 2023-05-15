/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/15 12:23:24 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd, env));
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd, env));
	if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(cmd, env));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd, env));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd));
	return (0);
}

// void	exec_builtin_fork(t_cmd *cmd, t_env *env)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_perror("fork");
// 	if (pid == 0)
// 	{
// 		if (!ft_strcmp(cmd->cmd, "echo"))
// 			ft_echo(cmd);
// 		if (!ft_strcmp(cmd->cmd, "cd"))
// 			ft_cd(cmd, env);
// 		if (!ft_strcmp(cmd->cmd, "pwd"))
// 			ft_pwd(cmd);
// 		if (!ft_strcmp(cmd->cmd, "export"))
// 			ft_export(cmd, env);
// 		if (!ft_strcmp(cmd->cmd, "env"))
// 			ft_env(cmd, env);
// 		if (!ft_strcmp(cmd->cmd, "unset"))
// 			ft_unset(cmd, env);
// 		if (!ft_strcmp(cmd->cmd, "exit"))
// 			ft_exit(cmd);
// 		exit(0);
// 	}
// 	else
// 		wait(&pid);
// }

void	execute_cmd(t_list *cmd, t_env *env)
{
	// pid_t	pid;
	// int		fd[2] = {-1, -1};
	// old_fd = fd[];
	(void)env;

	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd) && g_minishell.n_commands == 1)
	{
		g_minishell.exit_status = exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), env);	//exec in parrent
		return ;
	}
	// pid = fork();
	// if (pid < 0)
	// 	perror("fork");
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], );
	// }
}

void	execute(t_list *list, t_env *env)
{
	t_list *curr_cmd = list;

	while (curr_cmd)
	{
		execute_cmd(curr_cmd, env);
		curr_cmd = curr_cmd->next;
	}
	
	printf(">>> EXIT_STATUS = [%d]\n", g_minishell.exit_status);
}
