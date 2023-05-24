/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:06:33 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 12:07:30 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef environment_H
# define environment_H

#include "minishell.h"

// function that initialize the t_env from env
t_env		*ft_init_env(char **env);
t_list		*ft_lst_list_holder(char **env);
// function that set value to t_env from user
// function that replace value from key in t_env with new one
void		ft_setenv(t_env **env, char *key, char *value);
// function that get value of a special key
char		*ft_getenv(t_env *env, char *key);
//free
void		ft_free_env(t_env **env_t);

void		ft_unset_env_list(t_list **env_l, char *key);
void		ft_unset_env_table(char **env_table, size_t index);

// function used in unset.c
ssize_t	get_env_index(char **env_table, char *key);

t_env *g_env_s(t_env *env);

#endif