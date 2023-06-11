/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:40 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/11 17:30:12 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
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
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd));
	if (!ft_strcmp(cmd->cmd, "env"))
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

	if (is_builtin(((t_cmd *)(cmd->content))->cmd))
	{
		status = exec_builtin(((t_cmd *)(cmd->content)), list);
		exit(status);
	}
}

int	execb1(t_list *cmd, t_list *list, int *get_exit, t_execve_params *ep)
{
	size_t	n_commands;

	n_commands = ft_lstsize(list);
	if (is_builtin(((t_cmd *)(cmd->content))->cmd) && n_commands == 1)
	{
		free(ep->args);
		free(ep->path);
		g_exit_status = exec_builtin(((t_cmd *)(cmd->content)), list);
		*get_exit = 0;
		return (1);
	}
	return (0);
}
