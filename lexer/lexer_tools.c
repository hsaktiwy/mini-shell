/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/02 19:34:10 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_list **tokens, int *index, int *cmd)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	add_fake_cmd(tokens, *cmd);
	token->type = PIPE;
	token->value = NULL;
	g_pipe_count(g_pipe_count(-1) + 1);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*index)++;
	*cmd = 0;
}

// this int return  is weird need to get more check ?
void	handle_command_helper(t_cmd **cmd)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split((*cmd)->cmd, '#');
	free((*cmd)->cmd);
	(*cmd)->cmd = tab[0];
	while (tab[++i])
		ft_lstadd_back(&((*cmd)->arg), ft_lstnew(creat_arg(tab[i], WORD)));
	(*cmd)->cmd_type = WORD;
}

int	handle_command(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	t_cmd	*cmd;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = COMMAND;
	token->value = get_cmd(env, &input[*index], index);
	if (token->value)
	{
		cmd = token->value;
		if (!(str_iswhitespaced(cmd->cmd) && cmd->cmd_type != VARIABLE))
		{
			cmd->cmd = iswildcards(cmd->cmd, VARIABLE);
			handle_command_helper(&cmd);
		}
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (1);
	}
	else
		free(token);
	return (0);
}

void	handle_arg_helper(char *file, t_token **cmd)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(file, '#');
	while (tab[++i])
		ft_lstadd_back(&(((t_cmd *)(*cmd)->value)->arg),
			ft_lstnew(creat_arg(tab[i], WORD)));
}

void	handle_arg(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*cmd;
	t_list	*node;
	char	*file;

	cmd = NULL;
	node = NULL;
	cmd = last_cmd(tokens);
	if (is_splitable_env(&input[*index]))
	{
		file = get_simple_arg(env, &input[*index], index);
		file = iswildcards(file, VARIABLE);
		handle_arg_helper(file, &cmd);
	}
	else
	{
		file = get_simple_arg(env, &input[*index], index);
		file = iswildcards(file, WORD);
		handle_arg_helper(file, &cmd);
	}
	free(file);
}
