/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:37:42 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/07 20:54:58 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cond_env_expand(char c, char next_c)
{
	return ((c == '$' && next_c && (ft_isalpha(next_c) || next_c == '{'
				|| next_c == '*' || next_c == '?' || next_c == '_')
			&& !iswhitespace(next_c)));
}

int	cond_env_expand_input(char next_c)
{
	return (ft_isalpha(next_c) || next_c == '?' || next_c == '\''
		|| next_c == '\"' || next_c == '*' || next_c == '{'
		|| next_c == '_');
}

int	cond_get_token_one(char str, char c)
{
	return (str && ((!c && str != '|'
				&& str != '<' && str != '>' 
				&& !iswhitespace(str)) || c));//&& str != '#'
}

int	cond_get_token_sec(char str, char t_c, char c)
{
	return (t_c == c && str && ((!c && str != '|'
				&& str != '<' && str != '>'
				&& !iswhitespace(str)) || c));
}

char	*expand(char *line)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strdup("");
	while (line[i])
	{
		if (line[i + 1] && cond_env_expand(line[i], line[i + 1]))
			arg = go_to_expand_var(arg, line, &i, '\"');
		else if (line[i])
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i++], 1);
		}
	}
	return (arg);
}
