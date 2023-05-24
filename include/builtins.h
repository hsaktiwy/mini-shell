/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 14:47:47 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_echo(t_cmd *command);
int		ft_cd(t_cmd *command);
int		ft_pwd(t_cmd *command);
int		ft_export(t_cmd *command);
int		ft_env(t_cmd *command);
int		ft_unset(t_cmd *command);
int		ft_exit(t_cmd *command, t_list *list);
//common functions
int		check_key(char *key);
int 	print_error2(char *identifier, int i);

// error handling
int	print_error(char *command, char *str_error, int print_error);
#endif