/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:59:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 20:27:03 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// helper to check input
void	s_free(void *value);
char	*get_token(char *str);
char	*expand_env_var(char *s, char *res, int *k);
t_file	*get_file(t_env *env, char *input, int *index);
t_file	*creat_arg(char *file_name);
t_cmd	*init_cmd(void);

// lexer
int		lexer(t_list **tokens, char *input, t_env *env);
void	free_tokens(t_list **list);
// void	free_token(void *value);
int		handle_command(t_list **tokens, t_env *env, char *input, int *index);
void	handle_arg(t_list **tokens, t_env *env, char *input, int *index);
void	handle_pipe(t_list **tokens, int *index, int *cmd);
void	ini_arg_count(t_list **tokens);
int		parser_erreur(char	*input);

char	*get_initial_arg(char *str);
t_list	*turn_command_to_lst(char *ini_t_r);
void	wildcard_the_list(t_list **list);
void	handle_arg_helper(char *file, t_token **cmd);
void	handle_command_helper(t_cmd **cmd, char *args);

t_token	*last_cmd(t_list **tokens);
int		get_start(char *str);
void	add_fake_cmd(t_list **tokens, int cmd);
char	*here_doc_name(char *common, int nbr);
void	lexer_err(char *str);
// expand functions
char	*expand_input(t_env *env, char *line);
char	*expand(char *line);
int		cond_env_expand_input(char next_c);
int		cond_get_token_one(char str, char c);
int		cond_get_token_sec(char str, char t_c, char c);
char	*go_to_expand_var(char *arg, char *line, int *i, char c);
char	*reallocated_str(char *str, char *add);
char	*add_back(char *arg, char *input, char *c);
char	*add_front(char *arg, char *input, char *c);
char	*encapsulation(char *str);

int		check_redirection(char *input);
// this is for test delete this before pushing and validate the project
void	display_tokens(t_list	*tokens);
void	show_time(char *str);

// wildcards
char	*iswildcards(char *input, char	*ini_s);
char	double_or_single(char input, char old_c);
int		isendwith(char *string);
char	*local_dir(char *tmp);
char	*get_initial_token(char *str);
int		input_arg_size(char *str);
char	double_single_check(char input, char old_c, int *i, int *v);
char	*get_heredoc_token(char *str);

#endif