/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:52:33 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/09 18:56:54 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_piping(char *input)
{
	int		i;
	int		open;
	char	c;

	open = -1;
	i = 0;
	c = '\0';
	if (input[i] == '|')
		return (0);
	while (input[i] && input[i] != '#' && ft_isprint(input[i]))
	{
		c = double_or_single(input[i], c);
		if (!c && input[i] == '|' && open != 1)
			open = 1;
		else if (input[i] != '|' && !iswhitespace(input[i]) && open == 1)
			open = 0;
		else if (!c && input[i] == '|' && open == 1)
			break ;
		i++;
	}
	if (open == 1)
		return (0);
	return (1);
}

int	printf_error(int boolean)
{
	if (boolean == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		script_line();
		ft_putstr_fd("syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		if (g_script_mode(-1))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			script_line();
			ft_putstr_fd("`", STDERR_FILENO);
			ft_putstr_fd(g_input_line(NULL), STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			before_exiting2();
		}
		return (1);
	}
	return (0);
}

void	syntaxe_error_display(t_list *list, t_token *tmp, char *c)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	script_line();
	ft_putstr_fd("syntax error near unexpected token `",
		STDERR_FILENO);
	if (list && tmp->type != COMMAND && c[0])
	{
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("newline'\n", STDERR_FILENO);
	if (g_script_mode(-1))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		script_line();
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(g_input_line(NULL), STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		before_exiting2();
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
