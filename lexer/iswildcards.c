/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iswildcards.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lol <lol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
/*   Updated: 2023/05/28 19:33:26 by lol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	double_or_single(char input, char old_c, int *i)
{
	if (input == '\'' && old_c == '\0')
		old_c = '\'';
	else if (input == '\"' && old_c == '\0')
		old_c = '\"';
	else if (input == old_c)
		old_c = '\0';
	(*i)++;
	return (old_c);
}

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
	//printf("%d\n",isendwith(exp));
	if (!points[i] && exp[0] != '*' && !isendwith(exp))
	{
		tmp = strstr(string, points[0]);
		if (!isendwith(exp) && string == tmp)
		{
			tmp = strstr(string, points[i - 1]);
			tmp = &tmp[strlen(points[i - 1])];
	//		printf("%c\n", *tmp);
			if (!*tmp)
				return (fre_tab(points), 1);
		}
		else if (string == tmp)
			return (fre_tab(points), 1);
	}
	if (!points[i] && exp[0] != '*' && isendwith(exp))
	{
		tmp = strstr(string, points[0]);
		if (string == tmp)
			return (fre_tab(points), 1);
	}
	else if (!points[i] && !isendwith(exp))
	{
		tmp = &tmp[strlen(points[i - 1])];
	//	printf("%c\n", *tmp);
		if (!*tmp)
			return (fre_tab(points), 1);
	}
	else if (!points[i])
		return (fre_tab(points), 1);
	return (fre_tab(points), 0);
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

char	*add_matchs(struct dirent *entry, char *arg,char	*tmp, int *i)
{
	char 	*res;

	res = arg;
	if (entry)
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
char	*process_wildcard_argument(char	*arg, char *input, int *i);
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
	res = local_dir(res, tmp2);
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
			c = double_or_single(input[i], c, &i);
		}
		else if (input[i] == '*' && c == '\0' && red == 0)
		{
			///
			//printf("stetp1: %s\n", arg);
			// int j = 0;
			// while (input[i + j] && (!iswhitespace(input[i + j]) && input[i + j] != '>'
			// && input[i + j] != '<' && input[i + j] != '|'))
			// {
			// 	arg = ft_realloc(arg, ft_strlen(arg) + 2);
			// 	ft_strncat(arg, &input[i + j], 1);
			// 	j++;	
			// }
			// ///
			// //printf("stetp2: %s(i = %d,j = %d)\n",arg, i,j);
			// int x = ft_strlen(arg) - 1;
			// //printf("x = %c\n", arg[x]);
			// while (arg[x] && (!iswhitespace(arg[x]) && arg[x] != '>'
			// && arg[x] != '<' && arg[x] != '|'))
			// 	x--;
			// ///
			// //printf("stetp3 : %s\n", arg);
			// char *tmp;
			// tmp = ft_strdup(&arg[++x]);
			// arg[x] = '\0';
			// //printf("tmp = %s _ (arg : %s)\n", tmp, arg);
			// arg = ft_realloc(arg, ft_strlen(arg) + 1);
			// /// now lets crete add our matched string
			// //printf("stetp4 : %s\n", arg);
			// DIR *dir;
			// dir = opendir(".");
			// if (dir)
			// {
			// 	struct dirent *entry;
			// 	do
			// 	{
			// 		entry = readdir(dir);
			// 		if (entry)
			// 		{
			// 			if (ft_regx(entry->d_name, tmp))
			// 			{
			// 				arg = str_join(arg, ft_strdup(" "));
			// 				arg = str_join(arg, ft_strdup(entry->d_name));
			// 			}
			// 		}
			// 	} while (entry);
			// 	closedir(dir);
			// }
			// i += j;
			// free(tmp);
			arg = process_wildcard_argument(arg, input, &i);
			//printf("end %s\n", arg);
		}
		else
			arg = add_to_arg(arg, input, &i, &red);
	}
	free(input);
	g_input_line(arg);
	return (arg);
}
