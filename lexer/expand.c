/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:37:42 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/06 20:16:17 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cond_env_expand(char c, char next_c)
{
	return ((c == '$' && next_c && (ft_isalpha(next_c) || next_c == '{'
				| next_c == '?' || next_c == '_') && !iswhitespace(next_c)));
}

int	cond_env_expand_todefinekey(char c)
{
	return ((c && c != '?' && c != '{' && (ft_isalnum(c) || c == '_')));
}

char	*expand(t_env *env, char *line)
{
	int		i;
	int		k;
	char	*arg;

	i = 0;
	arg = ft_strdup("");
	while (line[i])
	{
		if (line[i + 1] && cond_env_expand(line[i], line[i + 1]))
		{
			k = 0;
			while (cond_env_expand_todefinekey(line[k + i + 1]))
				k++;
			if (line[k + i + 1] == '?')
				k++;
			arg = expand_env_var(env, &line[i + 1], arg, &k);
			i += k + 1;
		}
		else if (line[i])
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i++], 1);
		}
	}
	return (arg);
}
