/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:39 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 20:36:48 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handleHereDoc(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	*index += 2;
	char 	*r = get_token(&input[*index]);
	token->type = HERE_DOC;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handleInRedirect(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	++(*index);
	char 	*r = get_token(&input[*index]);
	token->type = IN_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handleAppendRedirect(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
		
	*index += 2;
	char 	*r = get_token(&input[*index]);
	token->type = APPEND_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
	
}

void handleOutRedirect(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token *token;
	;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
	
	++(*index);
	char 	*r = get_token(&input[*index]);
	token->type = OUT_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void handlePipe(t_list **tokens, int *index, int *cmd)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return;
	if ((*cmd) == 0)
	{
		t_token *fake_cmd = (t_token *)malloc(sizeof(t_token));
		if (!fake_cmd)
			return;
		fake_cmd->type = COMMAND;
		fake_cmd->value = ini_cmd(g_env_s(NULL));
		ft_lstadd_back(tokens, ft_lstnew(fake_cmd));
	}
	token->type = PIPE;
	token->value = NULL;
	g_pipe_count(g_pipe_count(-1) + 1);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*index)++;
	*cmd = 0;
}

int lexer(t_list **tokens, char *input, t_env *env)
{
	int i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (input[i] && input[i] != '#')
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
			handleHereDoc(tokens, env, input, &i);
		else if (input[i] == '<' && input[i + 1] != '<')
			handleInRedirect(tokens, env, input, &i);
		else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
			handleAppendRedirect(tokens, env, input, &i);
		else if (input[i] == '>' && input[i + 1] != '>')
			handleOutRedirect(tokens, env, input, &i);
		else if (input[i] == '|')
			handlePipe(tokens, &i, &cmd);
		else if (cmd == 0)
			cmd = handleCommand(tokens, env, input, &i);
		else
			handleArg(tokens, env, input, &i);
		if (iswhitespace(input[i]))
			i++;
	}
	if(cmd == 0)
	{
		t_token *fake_cmd = (t_token *)malloc(sizeof(t_token));
		if (!fake_cmd)
			return 0;
		fake_cmd->type = COMMAND;
		fake_cmd->value = ini_cmd(g_env_s(NULL));
		ft_lstadd_back(tokens, ft_lstnew(fake_cmd));
	}
	return 0;
}
