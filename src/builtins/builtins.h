/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:46 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/09 19:16:21 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H


# include "../../include/include.h"

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int	ft_echo(t_cmd *command);
int	ft_cd(t_cmd *command, t_env *env);
int	ft_pwd(t_env *env);

// error handling
int	print_error(char *command, char *str_error, int print_error);
#endif