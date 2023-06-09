/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:33:26 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/07 19:33:33 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*add_back(char *arg, char *input, char *c)
{
	char	*res;

	res = ft_realloc(arg, ft_strlen(arg) + 3);
	ft_strncat(res, input, 1);
	if (input[0] == '\'')
		ft_strncat(res, "\"", 1);
	else
		ft_strncat(res, "\'", 1);
	*c = double_or_single(input[0], *c);
	return (res);
}

char	*add_front(char *arg, char *input, char *c)
{
	char	*res;

	res = ft_realloc(arg, ft_strlen(arg) + 3);
	if (input[0] == '\'')
		ft_strncat(res, "\"", 1);
	else
		ft_strncat(res, "\'", 1);
	ft_strncat(res, input, 1);
	*c = double_or_single(input[0], *c);
	return (res);
}

char	*encapsulation(char *str)
{
	int		i;
	char	*res;
	char	c;

	i = -1;
	c = '\0';
	res = ft_strdup("");
	while (str[++i])
	{
		if (!c && (str[i] == '\'' || str[i] == '\"'))
			res = add_front(res, &str[i], &c);
		else if (c && c == str[i])
			res = add_back(res, &str[i], &c);
		else
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &str[i], 1);
		}
	}
	return (res);
}

char	*add_c_to_string(char	*arg, char *str, int *i)
{
	char	*res;

	res = arg;
	res = ft_realloc(res, ft_strlen(res) + 2);
	ft_strncat(res, &str[*i], 1);
	(*i)++;
	return (res);
}

char	*get_heredoc_token(char *str)
{
	int		i;
	char	c;
	char	*res;
	int		c_change;
	int		t_c;

	i = 0;
	c_change = 0;
	c = '\0';
	res = NULL;
	surpace_whitesspaces(str, &i);
	while (cond_get_token_one(str[i], c))
	{
		t_c = c;
		c = double_single_check(str[i], c, &i, &c_change);
		if (!c && str[i] == '$' && str[i + 1]
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (cond_get_token_sec(str[i], t_c, c))
			res = add_c_to_string(res, str, &i);
	}
	if (c_change && !res)
		res = ft_strdup("");
	return (res);
}
