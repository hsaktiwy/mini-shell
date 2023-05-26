/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:46:18 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 13:50:01 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_s(t_env *env)
{
	static t_env	*g_env;

	if (env == NULL)
		return (g_env);
	else
		g_env = env;
	return (NULL);
}

void	ft_declare_envs(t_env *env)
{
	char	path[4096];

	ft_setenv(&env, "OLDPWD", NULL);
	getcwd(path, 4096);
	ft_setenv(&env, "PWD", path);
	ft_setenv(&env, "_", "minishell");
}

void	ft_unset_oldpwd(t_env **env)
{
	ssize_t	index;

	ft_unset_env_list(&((*env)->l_env), "OLDPWD");
	index = get_env_index((*env)->env, "OLDPWD");
	if (index >= 0)
		ft_unset_env_table((*env)->env, index);
	ft_setenv(env, "OLDPWD", NULL);
}
