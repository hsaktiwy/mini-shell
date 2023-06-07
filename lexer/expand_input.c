/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:50:13 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/07 15:03:06 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//g_input_line(p); it was inthe remove_white_spaces but i remove 
//it cause it gave faulse alarm every expand of input
char	*remove_white_spaces(char *p)
{
	char	*tmp;

	tmp = p;
	// printf("??\n");
	p = ft_strtrim(tmp, " ");
	// printf("maybe\n");
	free(tmp);
	return (p);
}

char	*expand_tilde(t_env *env, char *arg, char *line, int *i)
{
	char	*res;

	res = arg;
	if (ft_getenv(env, "HOME"))
		res = reallocated_str(res, ft_getenv(env, "HOME"));
	else
	{
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &line[*i], 1);
	}
	(*i)++;
	return (res);
}

char	*go_to_expand_var(char *arg, char *line, int *i, char c)
{
	char	*res;
	int		k;

	res = arg;
	k = 0;
	if (!c && (line[*i + 1] == '\"' || line[*i + 1] == '\''))
		return ((*i)++, res);
	if (line[*i + 1] == '*')
		return ((*i) += 2, res);
	while (line[k + *i + 1] && line[k + *i + 1] != '?'
		&& line[k + *i + 1] != '{' && (ft_isalnum(line[k + *i + 1])
			|| line[k + *i + 1] == '_'))
		k++;
	if (line[k + *i + 1] == '{')
		k++;
	if (line[k + *i + 1] == '?')
		k++;
	res = expand_env_var(g_env_s(NULL), &line[*i + 1], res, &k);
	(*i) += k + 1;
	return (res);
}

char	*add_c_expanded_input(char *arg, char *line, int *s, char *c)
{
	char	*res;

	res = arg;
	*c = double_or_single(line[0], *c);
	if (!(*c) && (line[0] == '<' || line[0] == '>'))
		*s = 1;
	if (line[0] != '<' && line[0] != '>' && !iswhitespace(line[0]))
		*s = 0;
	res = ft_realloc(res, ft_strlen(res) + 2);
	ft_strncat(res, &line[0], 1);
	return (res);
}

char	*expand_input(t_env *env, char *line)
{
	int		i;
	char	c;
	int		s;
	char	*arg;

	i = 0;
	c = '\0';
	arg = ft_strdup("");
	s = 0;
	while (line[i])
	{
		if ((line[i] == '~' && (iswhitespace(line[i + 1]) || line[i + 1] == '\0'
					|| line[i + 1] == '/') && c == '\0'))
			arg = expand_tilde(env, arg, line, &i);
		else if (s == 0 && line[i] == '$' && line[i + 1] && (!c || (c == '\"'
					&& line[i + 1] != '\"' && line[i + 1] != '\''))
			&& cond_env_expand_input(line[i + 1]))
			arg = go_to_expand_var(arg, line, &i, c);
		else if (line[i])
		{
			arg = add_c_expanded_input(arg, &line[i], &s, &c);
			i++;
		}
	}
	return (free(line), remove_white_spaces(arg));
}
