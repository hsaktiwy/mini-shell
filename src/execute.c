/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/09 18:01:37 by aigounad         ###   ########.fr       */
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

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, env);
	if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(env);
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
		if (is_builtin(((t_cmd *)(((t_token *)(curr_cmd->content))->value))->cmd) /*&& there is one cmd*/)
			exec_builtin((t_cmd *)(((t_token *)(curr_cmd->content))->value), env);	//exec in parrent
		// else
		// 	exec_builtin_fork((t_cmd *)(((t_token *)(curr_cmd->content))->value)) //exec in child
		curr_cmd = curr_cmd->next;
	}
	
}