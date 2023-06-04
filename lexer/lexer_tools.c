/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/04 21:22:02 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_initial_token(char *str)
{
	int		i;
	char	*arg;
	char	c;

	c = '\0';
	i = 0;
	arg = ft_strdup("");
	while (str[i] && ((!c && str[i] != '#' && !iswhitespace(str[i])
			&& str[i] != '|' && str[i] != '<'  && str[i] != '>')
			|| c))
	{
		c = double_or_single(str[i], c);
		arg = ft_realloc(arg, ft_strlen(arg) + 2);
		ft_strncat(arg, &str[i], 1);
		i++;
	}
	return (arg);
}

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
	if (!(*(*cmd)->cmd))
		return ;
	tab = ft_split((*cmd)->cmd, '\n');
	free((*cmd)->cmd);
	(*cmd)->cmd = tab[0];
	while (tab[++i])
		ft_lstadd_back(&((*cmd)->arg), ft_lstnew(creat_arg(tab[i], WORD)));
	(*cmd)->cmd_type = WORD;
	free(tab);
}
void	cmd_helper(t_cmd *cmd, char *ini_t_r)
{
	char	**t_r;

	t_r = split(ini_t_r);
}

int	handle_command(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*token;
	t_cmd	*cmd;
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
	token->value = ini_cmd(env);
	if (token->value && tmp)
	{
		cmd = token->value;
		cmd->cmd = iswildcards(cmd->cmd, r);
		handle_command_helper(&cmd);
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (free(r), 1);
	}
	return (free(token), free(r), 0);
}

void	handle_arg_helper(char *file, t_token **cmd)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(file, '\n');
	while (tab[++i])
		ft_lstadd_back(&(((t_cmd *)(*cmd)->value)->arg),
			ft_lstnew(creat_arg(tab[i], WORD)));
	free(tab);
}
// if this work it will changes a lot of things
void	handle_arg(t_list **tokens, t_env *env, char *input, int *index)
{
	t_token	*cmd;
	t_list	*node;
	char	*file;
	char	*r;
	char	*tmp;

	cmd = NULL;
	node = NULL;
	printf("%s\n", &input[*index]);
	cmd = last_cmd(tokens);
	tmp = ft_strdup(&input[*index]);
	*index += input_arg_size(tmp);
	printf("-->%s\n", tmp);
	r = get_initial_token(tmp);
	file = expand_input(env, tmp);
	file = get_token(file);
	file = iswildcards(file, r);
	handle_arg_helper(file, &cmd);
	free(file);
	free(r);
}
