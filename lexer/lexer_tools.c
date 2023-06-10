/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 23:50:49 by aigounad         ###   ########.fr       */
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
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*index)++;
	*cmd = 0;
}

void	cmd_filer(t_token **cmd, char	*r)
{
	t_list	*c_args;
	t_list	*current;
	t_cmd	*command;

	command = ((t_cmd *)(*cmd)->value);
	c_args = turn_command_to_lst(r);
	wildcard_the_list(&c_args);
	current = c_args;
	if (current)
	{
		handle_command_helper(&command, current->content);
		current = current->next;
		while (current)
		{
			handle_arg_helper(current->content, cmd);
			current = current->next;
		}
	}
	ft_lstclear(&c_args, s_free);
}

void	arg_filer(t_token **cmd, char	*r)
{
	t_list	*c_args;
	t_list	*current;

	c_args = turn_command_to_lst(r);
	wildcard_the_list(&c_args);
	current = c_args;
	if (current)
	{
		while (current)
		{
			handle_arg_helper(current->content, cmd);
			current = current->next;
		}
	}
	ft_lstclear(&c_args, s_free);
}

int	handle_command(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	char	*r;
	char	*tmp;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = COMMAND;
	r = get_initial_token(&input[*index]);
	*index += input_arg_size(&input[*index]);
	tmp = ft_strdup(r);
	tmp = expand_input(env, tmp);
	token->value = init_cmd();
	if (token->value && tmp)
	{
		cmd_filer(&token, tmp);
		if (((t_cmd *)(token->value))->cmd)
		{
			ft_lstadd_back(tokens, ft_lstnew(token));
			return (free(r), free(tmp), 1);
		}
	}
	return (free(token), free(r), free(tmp), 0);
}

void	handle_arg(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*cmd;
	char	*file;
	char	*r;
	char	*tmp;

	cmd = NULL;
	cmd = last_cmd(tokens);
	tmp = ft_strdup(&input[*index]);
	*index += input_arg_size(tmp);
	r = get_initial_token(tmp);
	file = expand_input(env, r);
	arg_filer(&cmd, file);
	free(file);
	free(tmp);
}
