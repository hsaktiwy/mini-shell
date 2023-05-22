/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:53:21 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/21 17:47:22 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../include/include.h"
# include <fcntl.h>
# include <errno.h>
# include "builtins/builtins.h"
# include "../include/environement/environement.h"

# include <signal.h>

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
typedef struct s_token
{
	t_token_type	type;
	void			*value;	
}t_token;

// structs used in execute.c for norminette
typedef struct s_fd
{
	int	fd[2];
	int	old_fd;
}	t_fd;

typedef struct s_execve_params
{
	char	*path;
	char	**args;
}	t_execve_params;

//
void	main2(char *input, t_env *env);
// lexer
int		lexer(t_list **tokens, char *input, t_env *env);
void    free_tokens(t_list **list);
void    free_token(void *value);
int		handleCommand(t_list **tokens, t_env *env,char *input, int *index);
void	handleArg(t_list **tokens, t_env *env,char *input, int *index);
void	fix_expanding_issue(t_list **tokens);
void	ini_arg_count(t_list **tokens);
int		lexical_erreur(char	*input);

// parser
t_list	*parser(t_env *env, t_list **tokens, char *input);
t_ast	*command(t_list **current);
int		redirection_habdling(t_env *env, t_list **tokens);
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
char    *expand_input(t_env *env, char *line);
// tests
void	display_tokens(t_list	*tokens);
void 	display_ast_types(t_ast *node, char *str);

//execution
void	execute(t_list *list);

//global functions
int		g_cmd_executing(pid_t newpid);
int		g_heredoc_executing(int i);
int		g_stdin_fd(int i);
t_list *g_token_l(t_list *tokens);
char	*g_input_line(char *input);

//tmp
int isFileDescriptorValid(int fd);

#endif
