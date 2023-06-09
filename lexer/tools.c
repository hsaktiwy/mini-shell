/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:03:54 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/08 16:38:13 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	next_is_not(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (iswhitespace(str[i]))
			i++;
		else if (str[i] == c)
			return (0);
		else
			break ;
	}
	return (1);
}

int	isnot_red_syntaxe_error(char *res, int *i)
{
	if (res[*i] == '>' && res[*i + 1] == '>')
		(*i)++;
	(*i)++;
	surpace_whitesspaces(&res[*i], i);
	if (!res[*i] || res[*i] == '|' || res[*i] == '>'
		|| res[*i] == '<')
		return (0);
	return (1);
}

int	check_redirection_helper(char *res, int *i, int *count, char *c)
{
	*c = double_or_single(res[*i], *c);
	if (!(*c) && res[*i] == '<' && res[*i + 1] && res[*i + 1] == '<')
	{
		(*i)++;
		if (isnot_red_syntaxe_error(res, i))
			return ((*count)++, 1);
		else
			return (0);
	}
	else if (!(*c) && (res[*i] == '<' || res[*i] == '>')
		&& !isnot_red_syntaxe_error(res, i))
		return (0);
	else if (!(*c) && res[*i] == '|')
	{
		if (*i == 0)
			return (0);
		else if (!next_is_not(&res[*i + 1], '|'))
			return (0);
		else if (!res[*i + 1])
			return (0);
	}
	return (1);
}

int	check_redirection(char *input)
{
	int		i;
	char	*res;
	t_env	*env;
	int		count;
	char	c;

	c = '\0';
	res = input;
	i = -1;
	count = 0;
	while (res[++i])
	{
		if (!check_redirection_helper(res, &i, &count, &c))
			break ;
	}
	if (count > 16)
	{
		ft_putstr_fd("minibash: maximum here-document count exceeded\n",
			STDERR_FILENO);
		env = g_env_s(NULL);
		ft_free_env(&env);
		free(input);
		exit(2);
	}
	return (1);
}

char	*get_initial_token(char *str)
{
	int		i;
	char	*arg;
	char	c;

	c = '\0';
	i = 0;
	arg = ft_strdup("");
	while (str[i] && ((!c && !iswhitespace(str[i])
				&& str[i] != '|' && str[i] != '<' && str[i] != '>')
			|| c))
	{
		c = double_or_single(str[i], c);
		arg = ft_realloc(arg, ft_strlen(arg) + 2);
		ft_strncat(arg, &str[i], 1);
		i++;
	}
	return (arg);
}
