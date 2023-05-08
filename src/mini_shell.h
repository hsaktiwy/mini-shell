/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:53:21 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 18:58:37 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../include/include.h"
# include <fcntl.h>
# include <errno.h>
# include "builtins/builtins.h"

typedef enum types{
	COMMAND,
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HERE_DOC,
	APPEND_REDIRECT,
}t_token_type;

// Grammar types 	// INPUT,
typedef enum g_types{
	G_COMMAND,
	S_COMMAND,
	PIPELINE,
	G_PIPE,
	REDIRECTION,
	CMD,
}t_g_types;

// ATS
typedef struct s_ast{
	int		type;
	void	*content;
	struct	s_ast *left;
	struct	s_ast *right;
}	t_ast;
// tokens 
typedef struct token
{
	t_token_type	type;
	void			*value;	
}t_token;

// execution
void	executer(char *input, t_env *env);
// lexer
int		lexer(t_list **tokens, char *input, t_env *env);
void    free_tokens(t_list **list);
void	handleCommand(t_list **tokens, t_env *env, char *input, int *index);
void	handleArg(t_list **tokens, t_env *env,char *input, int *index);
void	fix_expanding_issue(t_list **tokens);
void	ini_arg_count(t_list **tokens);
// parser
t_list	*parser(t_env *env, t_list **tokens, char *input);
t_ast	*command(t_list **current);
void	redirection_habdling(t_env *env, t_list **tokens);
//		redirection parte
int		out_append_red(t_file *tmp, int out_app);
int		here_doc_red(t_env *env, t_file *tmp);
int		heredoc(t_env *env, char *delimiter, int h_fd);
int		in_redirection(t_file *tmp);
int		find_delimeter(char *line, char *needle);
// ast tools
t_ast	*ast_new_node();
void	ast_add_l_r(t_ast *node, t_ast *n_left, t_ast *n_right);
void	ast_set_data(t_ast *node, t_g_types type, void *content);
// expand
char	*expand(t_env *env, char *line);
// tests
void	display_tokens(t_list	*tokens);
void 	display_ast_types(t_ast *node, char *str);
#endif