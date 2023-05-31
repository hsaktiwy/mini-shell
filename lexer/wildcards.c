/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
/*   Updated: 2023/05/31 16:02:37 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// check there is still strstr function and not ft_strstr ours ?

char	*wildcards_start(char *arg)
{
	int		x;
	char	*tmp;
	char	*res;
	char	*tmp2;

	res = arg;
	x = ft_strlen(arg) - 1;
	while (res[x] && (!iswhitespace(res[x]) && res[x] != '>'
			&& res[x] != '<' && res[x] != '|'))
		x--;
	tmp = ft_strdup(&res[++x]);
	res[x] = '\0';
	res = ft_realloc(res, ft_strlen(res) + 1);
	tmp2 = get_simple_arg(g_env_s(NULL), tmp, &x);
	res = add_wildcards_to_input(res, tmp2);
	free(tmp2);
	free(tmp);
	return (res);
}

char	*process_wildcard_argument(char	*arg, char *input, int *i)
{
	int		j;
	char	*res;

	j = 0;
	res = arg;
	while (input[*i + j] && (!iswhitespace(input[*i + j])
			&& input[*i + j] != '>' && input[*i + j] != '<'
			&& input[*i + j] != '|'))
	{
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &input[*i + j], 1);
		j++;
	}
	res = wildcards_start(res);
	(*i) += j;
	return (res);
}

char	*add_to_arg(char *arg, char *input, int *i, int *red)
{
	char	*res;

	res = arg;
	if (input[*i] == '<' || input[*i] == '>')
	{
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &input[*i], 1);
		(*i)++;
		*red = 1;
		if (input[*i] == '<' || input[*i] == '>')
		{
			res = ft_realloc(res, ft_strlen(res) + 2);
			ft_strncat(res, &input[*i], 1);
			(*i)++;
		}
	}
	else
	{
		if (*red == 1 && ft_isalnum(input[*i]))
			*red = 0;
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &input[*i], 1);
		(*i)++;
	}
	return (res);
}

char	*process_wildcards(char *arg, char	*input, int *i, int *red)
{
	char	*res;

	res = arg;
	if (i != 0 && (input[*i - 1] != '\'' || (input[*i + 1]
				&& input[*i + 1] != '\'')))
		res = process_wildcard_argument(res, input, i);
	else if (i == 0)
		res = process_wildcard_argument(res, input, i);
	else
		res = add_to_arg(res, input, i, red);
	return (res);
}

char	*iswildcards(char *input)
{
	char	c;
	int		i;
	char	*arg;
	int		red;

	i = 0;
	c = '\0';
	arg = ft_strdup("");
	red = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			c = double_or_single(input[i], c);
			arg = add_to_arg(arg, input, &i, &red);
		}
		else if (input[i] == '*' && c == '\0' && red == 0)
			arg = process_wildcards(arg, input, &i, &red);
		else
			arg = add_to_arg(arg, input, &i, &red);
	}
	g_input_line(arg);
	return (free(input), arg);
}
