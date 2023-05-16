/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/16 12:10:04 by aigounad         ###   ########.fr       */
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

static void	ft_free_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}

char *ft_get_full_path(char *cmd, t_env *env)
{
	char	**paths;
	char	path[4096];
	int		i = 0;
	int		j;
	int		k;

	paths = ft_split(ft_getenv(env, "PATH"), ':');
	while (paths[i])
	{
		j = 0;
		if (!paths[i][j])
			continue ;
		while (paths[i][j])
		{
			path[j] = paths[i][j];
			j++;
		}
		if (path[j - 1] != '/')
			path[j++] = '/';
		k = 0;
		while (cmd[k])
		{
			path[j++] = cmd[k++];
		}
		path[j] = 0;
		if (access(path, 0) == 0)
		{
			ft_free_tab(paths);
			return (ft_strdup(path));
		}
		i++;
	}
	ft_free_tab(paths);
	return (ft_strdup(cmd));
}

char	**ft_get_args(t_list *list)
{
	char	**args;
	size_t	size;
	t_list	*arg_list;
	char 	*curr_arg;
	size_t	index;

	size = 1 + ((t_cmd *)((t_token *)(list->content))->value)->arg_count;
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		ft_perror("minishell: malloc");
	args[size] = 0;
	arg_list = ((t_cmd *)((t_token *)(list->content))->value)->arg;
	index = 0;
	args[index++] = ((t_cmd*)((t_token*)(list->content))->value)->cmd;
	while (arg_list)
	{
		curr_arg = ((t_file *)(arg_list->content))->a_file;
		args[index++] = curr_arg;
		arg_list = arg_list->next;
	}
	return (args);
}

void	execute_cmd(t_list *cmd, char *path, char **args, t_env *env, int *get_exit)
{
	pid_t	pid;

	int		fd[2] = {-1, -1};
	int		old_fd;


	old_fd = fd[0];
	if (cmd->next)
		pipe(fd);
	// exec bultin in parrent
	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd) && g_minishell.n_commands == 1)
	{
		g_minishell.status = exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), env);	//exec in parrent
		*get_exit = 0;
		return ;
	}
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)	// in child
	{
		// dup stdin
		if (old_fd != -1)
		{
			dup2(old_fd, STDIN_FILENO);
			close(old_fd);
		}
		// dup stdout
		if (cmd->next /*&& ((t_cmd *)(list->content))->cmd_out == 1*/)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		// dup redirections
		// if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd))
		// 	exit(exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), env));
		//exec cmd
		execve(path, args, env->env);
		perror("execve");
		exit(127);
	}
	close(fd[1]);
	close(old_fd);
	if (!(cmd->next))
		waitpid(pid, &g_minishell.status, 0);
}

void	get_exit_status()
{
	if (WIFEXITED(g_minishell.status))
		g_minishell.status = WEXITSTATUS(g_minishell.status);
	else if (WIFSIGNALED(g_minishell.status))
	{
		printf("get name of signal\n");
		g_minishell.status = WTERMSIG(g_minishell.status) + 128;
	}
}

void	execute(t_list *list, t_env *env)
{
	t_list *curr_cmd = list;
	int		get_exit;
	char	*path;
	char	**args;

	get_exit = 1;
	// ft_piping();
	while (curr_cmd)
	{
		path = ft_get_full_path(((t_cmd*)((t_token*)(curr_cmd->content))->value)->cmd, env);
		args = ft_get_args(curr_cmd);
		execute_cmd(curr_cmd, path, args, env, &get_exit);
		free(path);
		free(args);
		curr_cmd = curr_cmd->next;
	}
	while (wait(NULL) != -1);
	if (get_exit)
		get_exit_status();
	
	printf(">>> EXIT_STATUS = [%d]\n", g_minishell.status);
}

// t_minishell g_minishell;
// int main(int ac, char **av, char **env)
// {
// 	t_env *s_env = ft_init_env(env);
// 	char *path = ft_get_full_path("lhjhs", s_env);
// 	free(path);
// 	ft_free_env(&s_env);
// }
