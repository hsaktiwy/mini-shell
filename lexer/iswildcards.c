/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iswildcards.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
/*   Updated: 2023/05/29 16:39:17 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// check there is still strstr function and not ft_strstr ours ? 

static void	fre_tab(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}
int isendwith(char *string)
{
	int i;

	if (string)
	{
		i = ft_strlen(string);
		if (string[i - 1] == '*')
			return (1);
	}
	return (0);
}

int	ft_regx(char *string, char *exp)
{
	char **points;
	char *tmp;
	int	i;
	int	corr;

	corr = 1;
	i = 0;
	tmp = string;
	points = ft_split(exp, '*');
	while (points[i])
	{
		//printf("%s\n",points[i]);
		i++;
	}
	i = 0;
	//printf("tmp = %s\n",string);
	while (tmp && *tmp && points[i])
	{
		tmp = strstr(tmp, points[i]);
	//	printf("s = %s\n",tmp);
		i++;
	}
	if (!tmp)
		return (0);
	if (!points[i] && exp[0] != '*' && corr)
	{
		tmp = strstr(string, points[0]);
		if (string < tmp)
			corr = 0;
	}
	//printf("corr =%d\n", corr);
	if (!points[i] && !isendwith(exp) && corr)
	{
		tmp = string;
		while (strstr(&tmp[1], points[i - 1]))
		{
			tmp = strstr(&tmp[1], points[i - 1]);
		}
		tmp = &tmp[ft_strlen(points[i - 1])];
		if (*tmp)
			corr = 0;
	}
	return (fre_tab(points), corr);
}


char	*add_to_arg(char *arg, char *input, int *i, int *red)
{
	char	*res;

	res = arg;
	if(input[*i] == '<' || input[*i] == '>')
	{
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &input[*i], 1);
		(*i)++;
		*red = 1;
		if(input[*i] == '<' || input[*i] == '>')
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

char	double_or_single(char input, char old_c)
{
	if (input == '\'' && old_c == '\0')
		old_c = '\'';
	else if (input == '\"' && old_c == '\0')
		old_c = '\"';
	else if (input == old_c)
		old_c = '\0';
	return (old_c);
}

char	*add_matchs(struct dirent *entry, char *arg,char	*tmp, int *i)
{
	char 	*res;

	res = arg;
	if (entry && entry->d_name[0] != '.')
	{
		if (ft_regx(entry->d_name, tmp))
		{
			res = str_join(res, ft_strdup(" "));
			res = str_join(res, ft_strdup(entry->d_name));
			(*i)++;
		}
	}
	return (res);
}

char	*local_dir(char *arg, char *tmp)
{
	char			*res;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	res = arg;
	dir = opendir(".");
	if (dir)
	{
		do
		{
			entry = readdir(dir);
			res = add_matchs(entry, res, tmp, &i);
		}while (entry);
		closedir(dir);
	}
	if (i == 0)
	{
		res = str_join(res, ft_strdup(" "));
		res = str_join(res, ft_strdup(tmp));
	}
	return (res);
}

char	*add_wildcards_to_input(char *input, char *tmp)
{
	char	*res;
	char	**tab;
	int		i;

	i = -1;
	res = input;
	printf("entred\n");
	if (str_iswhitespaced(tmp))
	{
		tab = ft_split(tmp, ' ');
		while (tab[++i])
		{
			printf("1entred\n");
			if (ft_strchr(tab[i], '*'))
				res = local_dir(res, tab[i]);
			else
			{
				res = str_join(res, ft_strdup(" "));
				res = str_join(res, ft_strdup(tab[i]));
			}
			printf("2entred\n");
		}
		fre_tab(tab);
	}
	else
		res = local_dir(res, tmp);
	printf("3entred\n");
	return (res);
}

char	*wildcards_start(char *arg)
{
	int 	x;
	char 	*tmp;
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
	// we had a problem avec this type of argumen export u = "s " command ls $u*$u nee to diaply a error on s but not on *s
	tmp2 = get_simple_arg(g_env_s(NULL), tmp, &x);
	printf("tmp = %s\n", tmp2);
	res = add_wildcards_to_input(res, tmp2);
	printf("tmp 2 = %s\n", tmp2);
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
	while (input[*i + j] && (!iswhitespace(input[*i + j]) && input[*i + j] != '>'
	&& input[*i + j] != '<' && input[*i + j] != '|'))
	{
		res = ft_realloc(res, ft_strlen(res) + 2);
		ft_strncat(res, &input[*i + j], 1);
		j++;	
	}
	res = wildcards_start(res);
	(*i) += j;
	return (res);
}

char	*process_wildcards(char *arg, char	*input, int *i, int *red)
{
	char 	*res;

	res = arg;
	if (i != 0 && (input[*i - 1] != '\'' || (input[*i + 1]
				&& input[*i + 1] != '\'')))
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
