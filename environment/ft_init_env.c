/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/26 13:53:04 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_holder	*ft_lstnewholder(char *key_val, char *pt_equal)
{
	t_holder	*holder;

	holder = (t_holder *)malloc(sizeof(t_holder));
	if (!holder)
		return (perror("malloc"), NULL);
	if (key_val)
	{
		if (!pt_equal)
		{
			holder->key = ft_strdup(key_val);
			holder->value = NULL;
		}
		else
		{
			holder->key = ft_substr(key_val, 0, pt_equal - key_val);
			if (!*(pt_equal + 1))
				holder->value = ft_strdup("");
			else
				holder->value = ft_substr(key_val, pt_equal - key_val + 1,
						ft_strlen(pt_equal + 1));
		}
		return (holder);
	}
	else
		return (free(holder), holder = NULL, NULL);
}

t_list	*ft_lst_list_holder(char **env)
{
	t_list		*list;
	int			i;
	t_holder	*holder;
	char		*pt_equal;

	i = -1;
	list = NULL;
	while (env[++i])
	{
		pt_equal = ft_strchr(env[i], '=');
		holder = ft_lstnewholder(env[i], pt_equal);
		if (holder)
			ft_lstadd_back(&list, ft_lstnew(holder));
	}
	return (list);
}

void	ft_change_shlvl(t_env **env)
{
	char	*shlvl;
	int		level;
	char	*tmp;

	level = 0;
	shlvl = ft_getenv(*env, "SHLVL");
	if (!shlvl)
		ft_setenv(env, "SHLVL", "1");
	else
	{
		level = ft_atoi(shlvl);
		level++;
		if (level > 999)
		{
			write(2, "minishell: warning: shell level (", 33);
			ft_putnbr_fd(level, 2);
			write(2, ") too high, resetting to 1\n", 27);
			level = 1;
		}
		else if (level < 1)
			level = 0;
		tmp = ft_itoa(level);
		ft_setenv(env, "SHLVL", tmp);
		free(tmp);
	}
}

t_env	*ft_init_env(char **env)
{
	t_env	*env_l;
	size_t	size;

	env_l = (t_env *)malloc(sizeof(t_env));
	if (!env_l)
		return (perror("malloc"), NULL);
	env_l->l_env = NULL;
	if (!env || !*env)
	{
		env_l->env = malloc(sizeof(char *));
		*(env_l->env) = NULL;
		ft_declare_envs(env_l);
	}
	else
	{
		size = ft_t_strlen(env);
		env_l->env = ft_t_strdup(env, size);
		env_l->l_env = ft_lst_list_holder(env);
		ft_unset_oldpwd(&env_l);
	}
	ft_change_shlvl(&env_l);
	g_env_s(env_l);
	return (env_l);
}
