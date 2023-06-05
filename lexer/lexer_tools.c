/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:46:31 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/05 13:17:03 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_arg_helper(char *file, t_token **cmd);
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
void	handle_command_helper(t_cmd **cmd, char *args)
{
	char	**tab;
	int		i;

	i = 0;
	// if (!(*(*cmd)->cmd))
	// 	return ;
	tab = ft_split(args, '\n');
	//free((*cmd)->cmd);
	(*cmd)->cmd = tab[0];
	while (tab[++i])
		ft_lstadd_back(&((*cmd)->arg), ft_lstnew(creat_arg(tab[i], WORD)));
	(*cmd)->cmd_type = WORD;
	free(tab);
}
	// function that splite the initial r; then re allocated it in a linked list

char	*get_initial_arg(char *str)
{
	int		i;
	char	*arg;
	char	c;

	c = '\0';
	i = 0;
	arg = ft_strdup("");
	while (str[i] && ((!c && !iswhitespace(str[i]))|| c))
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
		printf("tmp : %s : size :%d\n", tmp, size);
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

void	cmd_filer(t_token **cmd, char	*r)
{
	t_list	*c_args;
	t_list	*current;
	t_cmd	*command;

	command = ((t_cmd *)(*cmd)->value);
	c_args = turn_command_to_lst(r);
	// printf("1\n");
	wildcard_the_list(&c_args);
	// printf("2\n");
	current = c_args;
	// printf("3\n");
	if (current)
		handle_command_helper(&command, current->content);
	// printf("4\n");
	current = current->next;
	while (current)
	{
		handle_arg_helper(current->content, cmd);
		current = current->next;
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
	token->value = ini_cmd(env);
	if (token->value && tmp)
	{
		cmd_filer(&token, tmp);
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (free(r), free(tmp), 1);// that a weird behavior
	}
	return (free(token), free(r), free(tmp), 0);
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
	printf("--> r = %s\n", r);
	file = expand_input(env, tmp);
	printf("--> expand = %s\n", file);
	file = get_token(file);
	printf("--> tokened = %s\n", file);
	file = iswildcards(file, r);
	printf("--> whilded = %s\n", file);
	handle_arg_helper(file, &cmd);
	free(file);
	free(r);
}
