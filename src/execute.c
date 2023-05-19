/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:01:57 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/19 12:47:00 by aigounad         ###   ########.fr       */
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

void	append_filename(char *filename, char *path, char *des)
{
	int		j;
	int		k;

	j = -1;
	while (path[++j])
		des[j] = path[j];
	if (des[j - 1] != '/')
		des[j++] = '/';
	k = 0;
	while (filename[k])
		des[j++] = filename[k++];
	des[j] = 0;
}

char *get_full_path(char *filename, t_list *list)
{
	char	**paths;
	char	path[4096];
	int		i;
	t_env	*env;

	if (is_builtin(filename) || ft_strchr(filename, '/'))
		return (ft_strdup(filename));
	env = ((t_cmd *)(((t_token *)(list->content))->value))->env;
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	if (!paths)
		return (write(2, "minishell: PATH not set\n", 24), NULL);
	i = -1;
	while (paths[++i])
	{
		if (!*(paths[i]))
			continue ;
		append_filename(filename, paths[i], path);
		if (access(path, 0) == 0)
		{
			free_tab(paths);
			return (ft_strdup(path));
		}
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
int isFileDescriptorValid(int fd) {
    return fcntl(fd, F_GETFD) != -1;
}

void	dup_redirections(t_list *cmd)
{
	if (((t_cmd *)(((t_token *)(cmd->content))->value))->file_out)
	{
		dup2(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_out, STDOUT_FILENO);
		// close(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_out);
	}
	if (((t_cmd *)(((t_token *)(cmd->content))->value))->file_in)
	{
		dup2(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_in, STDIN_FILENO);
		// close(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd_in);
	}
}

void	execute_command(char *filename, char **args, char **env)
{
	execve(filename, args, env);
	write(2, "minishell: ", 11);
	perror(filename);
	if (errno == EACCES)	//The filename argument is a Dir and permission denied
	{
		exit(126);
	}
	else if (errno == ENOENT)	//No such file od directory
	{
		exit(127);
	}
}

void	execb2(t_list *cmd, t_list *list)
{
	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd))
	{
		exit(exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), list));
	}
}

int	execb1(t_list *cmd, t_list *list, int *get_exit)
{
	size_t	n_commands;

	n_commands = ft_lstsize(list);
	if (is_builtin(((t_cmd *)(((t_token *)(cmd->content))->value))->cmd) && n_commands == 1)
	{
		g_exit_status = exec_builtin((t_cmd *)(((t_token *)(cmd->content))->value), list);	//exec in parrent
		*get_exit = 0;
		return (1);
	}
	return (0);
}

void	close_pipe_and_free(char *path, char **args, int *fd, int old_fd)
{
	free(path);
	free(args);
	if (fd[1] > 0)
		close(fd[1]);
	if (old_fd > 0)
		close(old_fd);
}

void	wait_4_last_command(t_list *cmd, pid_t pid)
{
	if (!(cmd->next))
		waitpid(pid, &g_exit_status, 0);
}

void	command_not_found(t_list *cmd, int *get_exit)
{
	char	*p;

	p = ((t_cmd*)((t_token*)(cmd->content))->value)->cmd;
	write(2, "minishell: ", 11);
	write(2, p, ft_strlen(p));
	write(2, ": command not found\n", 20);
	*get_exit = 0;
	g_exit_status = 127;
}

void	close_open_fds(t_list *list)
{
	while (list)
	{
		if (((t_cmd *)(((t_token *)(list->content))->value))->cmd_in != 0)
			close(((t_cmd *)(((t_token *)(list->content))->value))->cmd_in);
		if (((t_cmd *)(((t_token *)(list->content))->value))->cmd_out != 1)
			close(((t_cmd *)(((t_token *)(list->content))->value))->cmd_out);
		list = list->next;
	}
}

void	execute_2(t_list *cmd, t_list *list, int *get_exit, int *fd, int old_fd)
{
	(void)list;
	pid_t	pid;
	char	*path;
	char	**args;

	path = get_full_path(((t_cmd*)((t_token*)(cmd->content))->value)->cmd, cmd);
	if (!path)
		return (command_not_found(cmd, get_exit));
	args = get_args(cmd);
	if (cmd->next)
		pipe(fd);
	if (execb1(cmd, list, get_exit))
		return ;
	pid = fork();
	if (pid < 0)
		perror("fork"); //
	if (pid == 0)
	{
		dup_stdin_and_stdout(cmd, fd, old_fd);
		dup_redirections(cmd);
		execb2(cmd, list);
		close_open_fds(list);
		execute_command(path, args, ((t_cmd*)((t_token*)(cmd->content))->value)->env->env);
	}
	close_pipe_and_free(path, args, fd, old_fd);
	wait_4_last_command(cmd, pid);
}

void	get_exit_status()
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		printf("get name of signal\n");
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	}
}

void	execute(t_list *list)
{
	t_list *curr_cmd;
	int		get_exit;
	int		fd[2];
	int		old_fd;

	curr_cmd = list;
	get_exit = 1;
	fd[0] = -1;
	fd[1] = -1;
	while (curr_cmd)
	{
		old_fd = fd[0];
		execute_2(curr_cmd, list, &get_exit, fd, old_fd);
		curr_cmd = curr_cmd->next;
	}
	while (wait(NULL) > -1)
				;
	close_open_fds(list); 
	if (get_exit)
		get_exit_status();
	
	unlink(".here_doc");
}

// t_minishell g_minishell;
// static void	f()
// {
// 	system("leaks a.out");
// }
// int main(int ac, char **av, char **env)
// {
// 	atexit(f);
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
