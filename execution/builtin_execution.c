/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:40 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/07 20:45:29 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "PWD")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "ENV")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_list *list)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd));
	if (!ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "PWD"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd));
	if (!ft_strcmp(cmd->cmd, "env") || !ft_strcmp(cmd->cmd, "ENV"))
		return (ft_env(cmd));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd, list));
	return (0);
}

void	execb2(t_list *cmd, t_list *list)
{
	int	status;

	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd))
	{
		status = exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value),
				list);
		exit(status);
	}
}

int	execb1(t_list *cmd, t_list *list, int *get_exit, t_execve_params *ep)
{
	size_t	n_commands;
	char	*cmd_name;
	t_cmd	*command;

	n_commands = ft_lstsize(list);
	cmd_name = ((t_cmd *)(((t_token *)(cmd->content))->value))->cmd;
	if (is_builtin(cmd_name) && n_commands == 1)
	{
		free(ep->args);
		free(ep->path);
		command = (t_cmd *)(((t_token *)(cmd->content))->value);
		g_exit_status = exec_builtin(command, list);
		*get_exit = 0;
		return (1);
	}
	return (0);
}
