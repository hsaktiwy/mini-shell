/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_simple_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:20:03 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 20:42:14 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*get_simple_arg(t_env *env, char *str, int *index)
{
	int		i;
	int		k;
	char	*arg;

	i = 0;
	arg = ft_strdup("");
	// printf("before annything in simple arg: %s\n", str);
	// while (iswhitespace(str[i]))
	// 	i++;
	while (str[i] && !iswhitespace(str[i]) && str[i] != '|'  && str[i] != '<'  && str[i] != '>')
	{
		k = 0;
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i + 1] == '?' ||  str[i + 1] == '_') && !iswhitespace(str[i + 1]))
		{
			while (str[k + i + 1] && str[k + i + 1] != '?' && (ft_isalnum(str[k + i + 1]) || str[k + i + 1] == '_'))
				k++;
			if (str[k + i + 1] == '?')
				k++;
			arg = expand_env_var(env ,&str[i + 1], arg, k);
			i += k + 1;	
		}
		else if (str[i] == '\'')
		{
			arg = ft_strjoin(arg, get_single_quote(env, &str[++i], index));
			break ;
		}
		else if (str[i] == '\"')
		{
			arg = ft_strjoin(arg, get_double_quote(env, &str[++i], index));
			break ;
		}
		else if(str[i] && !iswhitespace(str[i]))
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &str[i], 1);
			i++;
		}
		// printf("??? = %c _ %s\n", str[i], arg);
	}
	if (!ft_strlen(arg) && k != 0)
		return ((*index) += i, free(arg), NULL);
	// printf("--> final result to return : [%s]\n", arg);
	return ((*index) += i,arg);
}
