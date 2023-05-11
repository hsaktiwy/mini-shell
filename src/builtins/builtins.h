/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/11 19:08:27 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H


# include "../../include/include.h"

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_echo(t_cmd *command);
int		ft_cd(t_cmd *command, t_env *env);
int		ft_pwd(t_cmd *command);
int		ft_export(t_cmd *command, t_env *env);
int		ft_env(t_cmd *command, t_env *env);
int		ft_unset(t_cmd *command, t_env *env);
int		ft_exit(t_cmd *command, t_env *env);

//common functions
int		check_key(char *key);
int 	print_error2(char *identifier);

#endif