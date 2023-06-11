/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:31:17 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/11 17:31:46 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_c(t_execve_params *execve_params, t_env *env)
{
	execve(execve_params->path, execve_params->args, env->env);
	write(2, "minishell: ", 11);
	script_line();
	if (errno == ENOENT)
	{
		perror(execve_params->path);
		exit(127);
	}
	else
	{
		if (errno == EACCES && is_a_directory(execve_params->path) == 1)
		{
			write(STDERR_FILENO, execve_params->path,
				ft_strlen(execve_params->path));
			write(STDERR_FILENO, ": is a directory\n", 17);
		}
		else
			perror(execve_params->path);
		exit(126);
	}
}

void	ft_piping(t_list *cmd, t_fd *fd)
{
	if (cmd->next)
		if (pipe(fd->fd) == -1)
			perror("minishell: pipe");
}

void	dup_stdin_and_stdout(t_list *cmd, t_fd *fd)
{
	if (fd->old_fd != -1)
	{
		if (dup2(fd->old_fd, STDIN_FILENO) == -1)
			perror("minishell: dup2");
		if (close(fd->old_fd) == -1)
			perror("minishell: close");
	}
	if (cmd->next)
	{
		if (close(fd->fd[0]) == -1)
			perror("minishell: close");
		if (dup2(fd->fd[1], STDOUT_FILENO) == -1)
			perror("minishell: dup2");
		if (close(fd->fd[1]) == -1)
			perror("minishell: close");
	}
}

void	dup_redirections(t_list *cmd)
{
	char	*file;
	int		fd;

	file = ((t_cmd *)(cmd->content))->file_out;
	if (file)
	{
		fd = ((t_cmd *)(cmd->content))->cmd_out;
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("minishell: dup2");
	}
	file = ((t_cmd *)(cmd->content))->file_in;
	if (file)
	{
		if (ft_strncmp(file, "/tmp/.here_doc", 9) == 0)
		{
			fd = open(file, O_RDONLY, 0666);
			if (fd == -1)
				perror("minishell: open");
			((t_cmd *)(cmd->content))->cmd_in = fd;
		}
		else
			fd = ((t_cmd *)(cmd->content))->cmd_in;
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("minishell: dup2");
	}
}

char	**get_args(t_list *list)
{
	char	**args;
	size_t	size;
	t_list	*arg_list;
	char	*curr_arg;
	size_t	index;

	size = 1 + ((t_cmd *)(list->content))->arg_count;
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (perror("minishell: malloc"), NULL);
	arg_list = ((t_cmd *)(list->content))->arg;
	index = 0;
	args[index++] = ((t_cmd *)(list->content))->cmd;
	while (arg_list)
	{
		curr_arg = ((t_file *)(arg_list->content))->a_file;
		args[index++] = curr_arg;
		arg_list = arg_list->next;
	}
	args[index] = 0;
	return (args);
}
