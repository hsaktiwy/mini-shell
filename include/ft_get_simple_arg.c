/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_simple_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:20:03 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 19:29:06 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*get_simple_arg(char *str, int *index)
{
	int		i;
	int		k;
	char	*arg;

	i = 0;
		arg = ft_strdup("");
	while (str[i] && iswhitespace(str[i]))
		i++;
	while (str[i] && !iswhitespace(str[i]) && str[i] != '|'  && str[i] != '<'  && str[i] != '>')
	{
		if (str[i] == '$' && !iswhitespace(str[i + 1]))// && (ft_isalnum(str[i + 1]) || str[i + 1] == '?' ||  str[i + 1] == '_'))
		{
			k = 0;
			while (str[k + i + 1] && !iswhitespace(str[k + i + 1]))//&& (ft_isalnum(str[k + i + 1]) || str[k +i + 1] == '?' ||  str[k + i + 1] == '_'))
				k++;
			arg = expand_env_var(&str[i + 1], arg, k);
			i += k + 1;			
		}
		else if (str[i] == '\'')
		{
			arg = ft_strjoin(arg, get_single_quote(&str[++i], index));
			break ;
		}
		else if (str[i] == '\"')
		{
			arg = ft_strjoin(arg, get_double_quote(&str[++i], index));
			break ;
		}
		else if(str[i])
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &str[i], 1);
			i++;
		}
		
	}
	return ((*index) += i,arg);
}
