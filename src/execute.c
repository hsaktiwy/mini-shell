/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/13 12:21:16 by aigounad         ###   ########.fr       */
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
		!ft_strcmp(cmd, "cat") || ////////tmp
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
/*****************************************************/
// void	set_signal_handlers();

// // void	child_handler()
// // {
// // 	exit(0);
// // }

// int ft_cat(t_cmd *command, t_env *env)
// {
// 	(void)command;
// 	char *cmd[10] = {
// 		"/bin/cat",
// 		NULL,
// 	};
// 	int id = fork();
// 	if (id == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		execve(cmd[0], cmd, env->env);
	
// 	}
// 	else{
// 		wait(0);
// 	}
// 	return (0);
//}
/*************************************************/

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		g_minishell.exit_status = ft_echo(cmd);
	if (!ft_strcmp(cmd->cmd, "cd"))
		g_minishell.exit_status = ft_cd(cmd, env);
	if (!ft_strcmp(cmd->cmd, "pwd"))
		g_minishell.exit_status = ft_pwd(cmd);
	if (!ft_strcmp(cmd->cmd, "export"))
		g_minishell.exit_status = ft_export(cmd, env);
	if (!ft_strcmp(cmd->cmd, "env"))
		g_minishell.exit_status = ft_env(cmd, env);
	if (!ft_strcmp(cmd->cmd, "unset"))
		g_minishell.exit_status = ft_unset(cmd, env);
	//////////////////////////////////////
	// if (!ft_strcmp(cmd->cmd, "cat"))	//tmp
	// 	ft_cat(cmd, env);				//tmp
	if (!ft_strcmp(cmd->cmd, "exit"))
		g_minishell.exit_status = ft_exit(cmd, env);
}

void	exec_builtin_fork(t_cmd *cmd, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (!ft_strcmp(cmd->cmd, "echo"))
			ft_echo(cmd);
		if (!ft_strcmp(cmd->cmd, "cd"))
			ft_cd(cmd, env);
		if (!ft_strcmp(cmd->cmd, "pwd"))
			ft_pwd(cmd);
		if (!ft_strcmp(cmd->cmd, "export"))
			ft_export(cmd, env);
		if (!ft_strcmp(cmd->cmd, "env"))
			ft_env(cmd, env);
		if (!ft_strcmp(cmd->cmd, "unset"))
			ft_unset(cmd, env);
		if (!ft_strcmp(cmd->cmd, "exit"))
			ft_exit(cmd);
		exit(0);
	}
	else
		wait(&pid);
}

void	execute(t_list *list, t_env *env)
{
	t_list *curr_cmd = list;
	// t_list *curr_arg;
	// t_cmd *cmd_list = list->content->value;
	while (curr_cmd)
	{
		/////////////////// print the cmd and it's args////////////////////
		// printf("cmd = %s\n", ((t_cmd *)(((t_token *)(curr_cmd->content))->value))->cmd);
		// curr_arg = ((t_cmd *)(((t_token *)(curr_cmd->content))->value))->arg;
		// while (curr_arg)
		// {
		// 	printf("|%s|", ((t_file *)(curr_arg->content))->a_file);
		// 	curr_arg = curr_arg->next;
		// }
		// printf("\n\n");
		////////////////// builtins execution /////////////////////////////
		if (is_builtin(((t_cmd *)(((t_token *)(curr_cmd->content))->value))->cmd))
		{
			if (g_minishell.n_commands == 1)
				exec_builtin((t_cmd *)(((t_token *)(curr_cmd->content))->value), env);	//exec in parrent
			else
				exec_builtin_fork((t_cmd *)(((t_token *)(curr_cmd->content))->value), env); //exec in child
		}
		curr_cmd = curr_cmd->next;
	}
	printf(">>> EXIT_STATUS = [%d]\n", g_minishell.exit_status);
}