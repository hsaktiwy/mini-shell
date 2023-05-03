/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:53:21 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/04/30 19:26:31 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include "../include/include.h"

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
void	executer(char *input);


// lexer
int		lexer(t_list **tokens, char *input);
void    free_tokens(t_list **list);

// parser
t_ast	*parser(t_list *tokens);
t_ast	*command(t_list **current);
// ast tools
t_ast	*ast_new_node();
void	ast_add_l_r(t_ast *node, t_ast *n_left, t_ast *n_right);
void	ast_set_data(t_ast *node, t_g_types type, void *content);
#endif