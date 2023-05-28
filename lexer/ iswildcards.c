/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    iswildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lol <lol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:20 by lol               #+#    #+#             */
/*   Updated: 2023/05/28 17:14:56 by lol              ###   ########.fr       */
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
char	*iswildcards(char *input)
{
	char	c;
	int		i;
	char	arg;

	i = 0;
	c = '\0';
	arg = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'' || input == '\"')
		{
			c = double_or_single(input[i], c, &i);
		}
		else if (input[i] == '*' && c == '\0')
		{
			///
			int j = 0;
			while (input[i + j] && (!iswhitespace(input[i + j]) || input[i + j] != '>'
			|| input[i + j] != '<' || input[i + j] != '|'))
			{
				arg = ft_realloc(arg, ft_strlen(arg) + 2);
				ft_strncat(arg, &input[i + j], 1);
				j++;	
			}
			///
			int x = j + i - 1;
			while (input[i + j] && (!iswhitespace(input[i + j]) || input[i + j] != '>'
			|| input[i + j] != '<' || input[i + j] != '|'))
				x--;
			///
			char *tmp;
			tmp = ft_strdup(&input[++x]);
			input[x] = '\0';
			arg = ft_realloc(arg, x + 1);
			/// now lets crete add our matched string
			DIR *dir;
			dir = opendir(".");
			if (dir)
			{
				struct dirent *entry;
				do
				{
					entry = readdir(dir);
					if ()
					{
						
					}
				} while (entry);
				
				while ()
			}
			
			
		}
		else
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &input[i], 1);
			i++;
		}
	}
}