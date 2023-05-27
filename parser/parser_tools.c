/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:52:33 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 15:39:32 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_piping(char *input)
{
	int	c;
	int	open;

	open = -1;
	c = 0;
	if (input[c] == '|')
		return (0);
	while (input[c] && ft_isprint(input[c]))
	{
		if (input[c] == '|' && open != 1)
		{
			open = 1;
		}
		else if (input[c] != '|' && !iswhitespace(input[c]) && open == 1)
		{
			open = 0;
		}
		else if (input[c] == '|' && open == 1)
			break ;
		c++;
	}
	if (open == 1)
		return (0);
	return (1);
}

int	printf_error(int boolean)
{
	if (boolean == 0)
	{
		printf("mini-shell:	syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

void	syntaxe_error_display(t_list *list, t_token	*tmp, char *c)
{
	if (list && tmp->type != COMMAND && c[0])
	{
		ft_putstr_fd("mini-shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("mini-shell: syntax error near ,", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
	}
}

char	*special_token_show(t_token_type type)
{
	if (type == 1)
		return ("|");
	else if (type == 2)
		return ("<");
	else if (type == 3)
		return (">");
	else if (type == 4)
		return ("<<");
	else if (type == 5)
		return (">>");
	else
		return ("");
}

void	printf_error_redi(t_list *list)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*c;

	tmp = NULL;
	c = NULL;
	if (list)
	{
		tmp = list->content;
		if (tmp->type == COMMAND)
		{
			cmd = tmp->value;
			if (!(cmd->cmd))
			{
				list = list->next;
				if (list)
					tmp = list->content;
			}
		}
		c = special_token_show(tmp->type);
	}
	syntaxe_error_display(list, tmp, c);
}
