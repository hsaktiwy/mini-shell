/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/17 13:34:35 by aigounad         ###   ########.fr       */
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

static void	free_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}

int	is_path(char *s)
{
	if (ft_strchr(s, '/'))
		return (1);
	else
		return (0);
}

char *get_full_path(char *cmd, t_env *env)
{
	char	**paths;
	char	path[4096];
	int		i = 0;
	int		j;
	int		k;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (ft_strcmp(cmd, "minishell" == 0))
		return ()
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
			free_tab(paths);
			return (ft_strdup(path));
		}
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	**get_args(t_list *list)
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
		if (*curr_arg)
			args[index++] = curr_arg;
		arg_list = arg_list->next;
	}
	return (args);
}
void	dup_stdin_and_stdout(t_list *cmd, int *fd, int old_fd)
{
	// dup stdin
	if (old_fd != -1)
	{
		dup2(old_fd, STDIN_FILENO);
		close(old_fd);
	}
	// dup stdout
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	dup_redirections(t_list *cmd)
{
	if (((t_cmd *)(((t_token *)(cmd->content))->value))->file_out)
	{
		dup2(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_out, STDOUT_FILENO);
		close(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_out);
	}
	if (((t_cmd *)(((t_token *)(cmd->content))->value))->file_in)
	{
		dup2(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_in, STDOUT_FILENO);
		close(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_in);
	}
}

void	execute_command_in_child(char *path, char **args, char **env)
{
	// printf("path  = %s|\n", path);
	// int i = -1;
	// while (args[++i])
	// 	printf("arg[%d]  = [%s]\n", i,args[i]);
	execve(path, args, env);
	write(2, "minishell: ", 11);
	perror(path);
	exit(127);
}

void	execute_builtin_in_child(t_list *cmd, t_env *env)
{
	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd))
		exit(exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), env));
}

int	execute_builtin_in_parrent(t_list *cmd, t_env *env, int *get_exit)
{
	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd) && g_minishell.n_commands == 1)
	{
		g_minishell.status = exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), env);	//exec in parrent
		*get_exit = 0;
		return (1);
	}
	return (0);
}

void	close_fds_and_free(char *path, char **args, int *fd)
{
	free(path);
	free(args);
	if (fd[1] > 0)
		close(fd[1]);
}

void	wait_4_last_command(t_list *cmd, pid_t pid)
{
	if (!(cmd->next))
		waitpid(pid, &g_minishell.status, 0);
}

void	command_not_found(t_list *cmd)
{
	char	*p;

	p = ((t_cmd*)((t_token*)(cmd->content))->value)->cmd;
	write(2, p, ft_strlen(p));
	write(2, ": command not found\n", 21);
}

void	execute_2(t_list *cmd, t_env *env, int *get_exit, int *fd, int old_fd)
{
	pid_t	pid;
	char	*path;
	char	**args;

	path = get_full_path(((t_cmd*)((t_token*)(cmd->content))->value)->cmd, env);
	if (!path)
		return (command_not_found(cmd));
	args = get_args(cmd);
	if (cmd->next)
		pipe(fd);
	if (execute_builtin_in_parrent(cmd, env, get_exit))
		return ;
	pid = fork();
	if (pid < 0)
		perror("fork"); //
	if (pid == 0)
	{
		dup_stdin_and_stdout(cmd, fd, old_fd);
		dup_redirections(cmd);
		execute_builtin_in_child(cmd, env);
		execute_command_in_child(path, args, env->env);
	}
	close_fds_and_free(path, args, fd);
	wait_4_last_command(cmd, pid);
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
	t_list *curr_cmd;
	int		get_exit;
	int		fd[2];
	int		old_fd;

	curr_cmd = list;
	get_exit = 1;
	fd[0] = -1;
	fd[1] = -1;
	// ft_piping();
	while (curr_cmd)
	{
		old_fd = fd[0];
		execute_2(curr_cmd, env, &get_exit, fd, old_fd);
		if (old_fd > 0)
			close(old_fd);
		curr_cmd = curr_cmd->next;
	}
	while (wait(NULL) > -1)
				;
	if (get_exit)
		get_exit_status();
	
	printf(">>> EXIT_STATUS = [%d]\n", g_minishell.status);
	unlink(".here_doc");
}

// t_minishell g_minishell;
// int main(int ac, char **av, char **env)
// {
// 	t_list *list = malloc(sizeof(t_list));
// 	list->next = NULL;
// 	list->content = (t_token *)malloc(sizeof(t_token));
// 	((t_token *)(list->content))->value = (t_cmd *)malloc(sizeof(t_cmd));

// 	((t_cmd *)((t_token *)(list->content))->value)->arg = malloc(sizeof(t_list));
// 	((t_cmd *)((t_token *)(list->content))->value)->arg->content = malloc(sizeof(t_file));
// 	((t_file *)(((t_cmd *)((t_token *)(list->content))->value)->arg->content))->a_file = av[2];
// 	((t_cmd *)((t_token *)(list->content))->value)->arg->next = NULL;
// 	((t_cmd *)((t_token *)(list->content))->value)->arg_count = 1;
// 	((t_cmd *)((t_token *)(list->content))->value)->cmd = av[1];
// 	((t_cmd *)((t_token *)(list->content))->value)->cmd_in = 0;
// 	((t_cmd *)((t_token *)(list->content))->value)->cmd_out = 1;
// 	((t_cmd *)((t_token *)(list->content))->value)->file_in = NULL;
// 	((t_cmd *)((t_token *)(list->content))->value)->file_out = NULL;


// 	t_list *node;
// 	if (av[3] && av[4])
// 	{
// 		node = malloc(sizeof(t_list));
// 		list->next = node;
// 		node->next = NULL;
// 		node->content = (t_token *)malloc(sizeof(t_token));
// 		((t_token *)(node->content))->value = (t_cmd *)malloc(sizeof(t_cmd));

// 		((t_cmd *)((t_token *)(node->content))->value)->arg = malloc(sizeof(t_list));
// 		((t_cmd *)((t_token *)(node->content))->value)->arg->content = malloc(sizeof(t_file));
// 		((t_file *)(((t_cmd *)((t_token *)(node->content))->value)->arg->content))->a_file = av[4];
// 		((t_cmd *)((t_token *)(node->content))->value)->arg->next = NULL;
// 		((t_cmd *)((t_token *)(node->content))->value)->arg_count = 1;
// 		((t_cmd *)((t_token *)(node->content))->value)->cmd = av[3];
// 		((t_cmd *)((t_token *)(node->content))->value)->cmd_in = 0;
// 		((t_cmd *)((t_token *)(node->content))->value)->cmd_out = 1;
// 		((t_cmd *)((t_token *)(node->content))->value)->file_in = NULL;
// 		((t_cmd *)((t_token *)(node->content))->value)->file_out = NULL;
// 	}

// 	t_env *s_env = ft_init_env(env);

// 	execute(list, s_env);

// 	ft_free_env(&s_env);
// 	if (av[3] && av[4])
// 	{
// 		free(((t_cmd *)((t_token *)(node->content))->value)->arg->content);
// 		free(((t_cmd *)((t_token *)(node->content))->value)->arg);
// 		free(((t_token *)(node->content))->value);
// 		free(node->content);
// 		free(node);
// 	}

// 	free(((t_cmd *)((t_token *)(list->content))->value)->arg->content);
// 	free(((t_cmd *)((t_token *)(list->content))->value)->arg);
// 	free(((t_token *)(list->content))->value);
// 	free(list->content);
// 	free(list);
// }
