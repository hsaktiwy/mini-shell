/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:39 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/03 16:05:05 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	int		start;
	char	*r;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	*index += 2;
	r = get_token(&input[*index]);
	start = get_start(&input[*index]);
	g_heredoc_count(1);
	token->type = HERE_DOC;
	token->value = get_file(env, &input[*index], index);
	free(((t_file *)token->value)->a_file);
	((t_file *)token->value)->a_file = r;
	((t_file *)token->value)->token_file = here_doc_name("/tmp/.here_doc",
			g_heredoc_count(-1));
	((t_file *)token->value)->here_doc_exp = start;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void	handle_inredirect(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	char	*r;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	++(*index);
	r = get_token(&input[*index]);
	token->type = IN_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void	handle_appendredirect(t_list **tokens, t_env *env, char *input,
			int *index)
{
	t_token	*token;
	char	*r;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	*index += 2;
	r = get_token(&input[*index]);
	token->type = APPEND_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void	handle_outredirect(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	char	*r;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return ;
	++(*index);
	r = get_token(&input[*index]);
	token->type = OUT_REDIRECT;
	token->value = get_file(env, &input[*index], index);
	((t_file *)token->value)->token_file = r;
	ft_lstadd_back(tokens, ft_lstnew(token));
}

int	lexer(t_list **tokens, char *input, t_env *env)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (input[i] && input[i] != '#')
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
			handle_heredoc(tokens, env, input, &i);
		else if (input[i] == '<' && input[i + 1] != '<')
			handle_inredirect(tokens, env, input, &i);
		else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
			handle_appendredirect(tokens, env, input, &i);
		else if (input[i] == '>' && input[i + 1] != '>')
			handle_outredirect(tokens, env, input, &i);
		else if (input[i] == '|')
			handle_pipe(tokens, &i, &cmd);
		else if (cmd == 0)
			cmd = handle_command(tokens, env, input, &i);
		else
			handle_arg(tokens, env, input, &i);
		if (iswhitespace(input[i]))
			i++;
	}
	return (add_fake_cmd(tokens, cmd), 0);
}
