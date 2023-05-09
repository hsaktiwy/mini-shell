/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/09 14:55:43 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_builtin(char *cmd)
{
	// printf(">>>>>> %s\n", cmd);
	// while (1)
	// {
	// 	if (*cmd != 0)
	// 		write(1, &cmd, 1);
	// 	else
	// 	{
	// 		write(1, "0", 1);
	// 		break ;
	// 	}
	// 	cmd++;
	// }
	// return 0;
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

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	(void)env;
	(void)cmd;
	// if (!ft_strcmp(cmd->cmd, "echo"))
	// 	echo(cmd);
	// printf(">>>>>> %s\n", cmd->cmd);
	// return ;
	if (!ft_strcmp(cmd->cmd, "cd"))
		cd(cmd, env);
}

void	execute(t_list *list, t_env *env)
{
	t_list *curr_cmd = list;
	// t_list *curr_arg;
	// t_cmd *cmd_list = list->content->value;
	while (curr_cmd)
	{
		///////////////////// print the cmd and it's args////////////////////
		// printf("cmd = %s\n", ((t_cmd *)(((t_token *)(curr_cmd->content))->value))->cmd);
		// curr_arg = ((t_cmd *)(((t_token *)(curr_cmd->content))->value))->arg;
		// while (curr_arg)
		// {
		// 	printf("|%s|", ((t_file *)(curr_arg->content))->a_file);
		// 	curr_arg = curr_arg->next;
		// }
		// printf("\n\n");
		//////////////////// builtins execution/////////////
		if (is_builtin(((t_cmd *)(((t_token *)(curr_cmd->content))->value))->cmd) /*&& there is one cmd*/)
			exec_builtin((t_cmd *)(((t_token *)(curr_cmd->content))->value), env);	//exec in parrent
		// else
		// 	exec_builtin_fork((t_cmd *)(((t_token *)(curr_cmd->content))->value)) //exec in child
		curr_cmd = curr_cmd->next;
	}
	
}