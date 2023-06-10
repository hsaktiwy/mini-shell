/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:09:08 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 16:09:50 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_initial_arg(char *str)
{
	int		i;
	char	*arg;
	char	c;

	c = '\0';
	i = 0;
	arg = ft_strdup("");
	while (str[i] && ((!c && !iswhitespace(str[i])) || c))
	{
		c = double_or_single(str[i], c);
		arg = ft_realloc(arg, ft_strlen(arg) + 2);
		ft_strncat(arg, &str[i], 1);
		i++;
	}
	return (arg);
}

t_list	*turn_command_to_lst(char *ini_t_r)
{
	t_list	*store;
	int		size;
	char	*tmp;

	size = 0;
	store = NULL;
	while (ini_t_r[size])
	{
		tmp = get_initial_arg(&ini_t_r[size]);
		size += ft_strlen(tmp);
		surpace_whitesspaces(&ini_t_r[size], &size);
		ft_lstadd_back(&store, ft_lstnew(ft_strtrim(tmp, " ")));
		free(tmp);
	}
	return (store);
}

void	wildcard_the_list(t_list **list)
{
	t_list	*current;
	char	*tmp;
	char	*res;

	current = *list;
	while (current)
	{
		tmp = current->content;
		res = iswildcards(get_initial_arg(tmp), tmp);
		free(tmp);
		current->content = res;
		current = current->next;
	}
}

void	handle_arg_helper(char *file, t_token **cmd)
{
	char	**tab;
	int		i;

	i = -1;
	if (file)
	{
		if (!*file)
		{
			ft_lstadd_back(&(((t_cmd *)(*cmd)->value)->arg),
				ft_lstnew(creat_arg(ft_strdup(""), WORD)));
			return ;
		}
		tab = ft_split(file, '\n');
		while (tab[++i])
			ft_lstadd_back(&(((t_cmd *)(*cmd)->value)->arg),
				ft_lstnew(creat_arg(tab[i], WORD)));
		free(tab);
	}
}

void	handle_command_helper(t_cmd **cmd, char *args)
{
	char	**tab;
	int		i;

	i = 0;
	if (args)
	{
		if (!(*args))
		{
			(*cmd)->cmd = ft_strdup("");
			return ;
		}
		tab = ft_split(args, '\n');
		(*cmd)->cmd = tab[0];
		while (tab[++i])
			ft_lstadd_back(&((*cmd)->arg), ft_lstnew(creat_arg(tab[i], WORD)));
		// (*cmd)->cmd_type = WORD;
		free(tab);
	}
}
