/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:06:48 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/31 00:37:01 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

void	execute(t_list *list);
void	close_open_fds(t_list *list);
void	exec_c(t_execve_params *execve_params, t_env *env);
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_list *list);
void	execb2(t_list *cmd, t_list *list);
int		execb1(t_list *cmd, t_list *list, int *get_exit, t_execve_params *ep);
void	dup_redirections(t_list *cmd);
void	dup_stdin_and_stdout(t_list *cmd, t_fd *fd);
void	get_name_of_signal(int sig);
char	**get_args(t_list *list);
char	*findcmd(char *filename);
void	append_filename(char *filename, char *path, char *des);
int		ft_forking(t_list *cmd, t_list *list, t_fd *fd, t_execve_params *ep);
void	ft_piping(t_list *cmd, t_fd *fd);
void	command_not_found(t_list *cmd, int *get_exit);
void	wait_4_last_command(t_list *cmd, pid_t pid);
void	close_pipe(t_list *cmd, t_fd *fd);
void	save_cmd(t_execve_params *ep, t_env *env);
void	ft_perror(char *msg);
void	restore_signals_in_child(void);
void	ft_init_fd(t_fd *fd, int *get_exit);

char	*shell_init_pwd(char *pwd, int stat);

//tmp
int		isFileDescriptorValid(int fd);

#endif