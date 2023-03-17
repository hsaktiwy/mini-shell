/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:06 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 17:57:13 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*get_cuted_SQ_file(char *input,int sq_status);

int	iswhitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

// char	*next_arg(char *str, int *index)
// {
// 	int		i;
// 	int		j;
// 	char	*arg;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && iswhitespace(str[i]))
// 		i++;
// 	j = i;
// 	while (str[j] && !iswhitespace(str[j]))
// 		j++;
// 	if (j == i)
// 		return (NULL);
// 	arg = malloc(((j - i) + 1));
// 	arg[j - i] = '\0';
// 	j = 0;
// 	while (str[i + j] && !iswhitespace(str[i + j]))
// 	{
// 		arg[j] = str[i + j];
// 		j++;
// 	}
// 	return ((*index) += j + i, printf("(%d_%d)\n",*index, i),arg);
// }

char *get_arg_single(char *input, int *index)
{
	int i;
	int s;
	
	i = 0;
	s = -1;
	while (input[i])
	{
		if (input[i] && (s == -1 || s == 1) && input[i] == 32)
			break;
		else if (input[i] == '\'' )
	}
}

int	ft_strchr_count(char *input, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i] && input[i] != ' ')
	{
		if (input[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*get_var(char *input, int *index)
{
	int		i;
	char	*var;
	char	*res;

	i = 0;
	if (ft_isdigit(input[i + 1]))
		return ((*index) += 2, NULL);
	while (input[i] 
		&& (ft_isalpha(input[i]) || ft_isdigit(input[i]) || input[i] == '_'))
		i++;
	(*index) += i;
	var = malloc(i);
	var[i - 1] = 0;
	i = 0;
	while (input[i] 
		&& (ft_isalpha(input[i]) || ft_isdigit(input[i]) || input[i] == '_'))
	{
		var[i] = input[i];
		i++;
	}
	res = ft_strdup(getenv(var));
	return (free(var), res);
}

char	*get_cuted_DQ_file(char *input, int	sq_status)
{
	int		i;
	int		j;
	
	i = 0;
	while (input[i])
	{
		printf("-|->%s_%d\n",input, i);
		if (input[i] == '\"')
			sq_status++;
		else if (input[i] == '$')
		{
			if (sq_status == - 1)
			{
				input = ft_strjoin(ft_strdup(""), get_var(&input[i], &i));
			}
			else
			{
				input[i - 1] = '\0';
				input = ft_strjoin(input, get_var(&input[i], &i));
			}
		}
		else if (input[i] == '\'' && (sq_status || sq_status == -1))
		{
			if (sq_status)
			{
				input[i - 2] = '\0';
				input = ft_strjoin(input, get_cuted_SQ_file(&input[i], -1));
			}else
			{
				input[i] = '\0';
				input = ft_strjoin(input, get_cuted_SQ_file(&input[++i], 0));
			}
			break;
		}
		else if (sq_status == 0)
			input[i - 1] = input[i];
		if (sq_status == 1)
			input[i - 1] = '\0';
		i++;
		printf("-->%s_%d\n",input, i);
	}
	return (input);
}

char	*get_cuted_SQ_file(char *input, int	sq_status)
{
	int		i;
	int		j;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			sq_status++;
		else if (input[i] == '\"' && sq_status)
		{
			input[i - 2] = '\0';
			input = ft_strjoin(input, get_cuted_DQ_file(&input[i], -1));
			break;
		}else
			input[i - 1] = input[i];
		if (sq_status)
			input[i - 1] = '\0';
		i++;
	}
	return (input);
}

t_file	*get_file(char *input, int *index)
{
	t_file	*file;
	int	i;

	i = 0;
	if(!input)
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->a_file = ft_strdup("\0");
		file->arg_type = WORD;
		return (file);
	}
	else if (input[0] == '\''
		&& !(ft_strchr_count(input, '\'') % 2))
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->a_file = get_cuted_SQ_file(next_arg(input, index), -1);
	}else if (input[0] == '\"'
		&& !(ft_strchr_count(input, '\"') % 2))
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->a_file = get_cuted_DQ_file(next_arg(input, index), -1);
	}else if (!(ft_strchr_count(input, '\"') % 2) && !(ft_strchr_count(input, '\'') % 2))
	{
		printf("all\n");
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->a_file = get_cuted_DQ_file(next_arg(input, index), -1);
	}
	return (file);
}

int main(int argc, char **argv)
{
	t_file *file;
	int index;
	
	index = 0;
	file = get_file(argv[1], &index);
	if (file)
		printf("%s_%d\n",file->a_file, index);
	else
		printf("(NULL)\n");
}