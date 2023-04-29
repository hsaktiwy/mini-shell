/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:06 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 18:35:11 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_quotes_validity(char *input)
{
	char	c;
	int		i;

	i = 0;
	c = '\0';
	while (input[i] && input[i] != '|')
	{
		if(input[i] == '\'' && !c)
			c = '\'';
		else if (input[i] == '\'' && c == '\'')
			c = '\0';
		else if (input[i] == '\"' && !c)
			c = '\"';
		else if (input[i] == '\"' && c == '\"')
			c = '\0';
		i++;
	}
	if (!c)
		return (1);
	else
		return (0);
}

t_file	*get_file(char *input, int *index)
{
	t_file	*file;
	//int	i;

	//i = 0;
	file = NULL;
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
		&& check_quotes_validity(input))
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		(*index)++;
		file->a_file = get_single_quote(&input[(*index)], index);
		
	}else if (input[0] == '\"'
		&& check_quotes_validity(input))
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		(*index)++;
		file->a_file = get_double_quote(&input[(*index)], index);
	}
	else if (check_quotes_validity(input))
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->a_file = get_simple_arg( input, index);
	}
	return (file);
}

// void	leaks_func()
// {
// 	system("leaks a.out");
// }

// int main(int argc, char **argv)
// {
// 	t_file *file;
// 	int index;
// 	atexit(leaks_func);
// 	index = 0;
// 	file = get_file("\"$HOME/$PATH\"$_ asjkhgjkashdjk", &index);
// 	if (file)
// 		printf("%s_%d\n",file->a_file, index);
// 	else
// 		printf("(NULL)\n");
// 	if	(file)
// 		free(file->a_file);
// 		free(file);
// 	return (0);
// }
// compiling : gcc ft_next_arg.c ft_strlen.c ft_strncat.c ft_realloc.c ft_strdup.c ft_strjoin.c ft_is*