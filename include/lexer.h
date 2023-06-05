/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:59:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/05 14:37:16 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// helper to check input
void	ft_lstfree_t_file(t_list **node);
void	s_free(void *value);
char	*get_token(char *str);
char	*get_single_quote(t_env *env, char *s, int *index);
char	*get_double_quote(t_env *env, char *s, int *index);
char	*get_simple_arg(t_env *env, char *str, int *index);
char	*expand_env_var(t_env *env, char *s, char *res, int *k);
int		check_quotes_validity(char *input);
int		is_splitable_env(char *str);
t_file	*get_file(t_env *env, char *input, int *index);
// t_cmd	*get_cmd(t_env *env, char *input, int *index);
t_cmd	*get_cmd(char *cmd);
t_file	*creat_arg(char *file_name, t_argument_type type);
t_cmd	*ini_cmd(t_env *env);

// lexer
int		lexer(t_list **tokens, char *input, t_env *env);
void	free_tokens(t_list **list);
void	free_token(void *value);
int		handle_command(t_list **tokens, t_env *env, char *input, int *index);
void	handle_arg(t_list **tokens, t_env *env, char *input, int *index);
void	handle_pipe(t_list **tokens, int *index, int *cmd);
void	fix_expanding_issue(t_list **tokens);
void	ini_arg_count(t_list **tokens);
int		lexical_erreur(char	*input);

t_token	*last_cmd(t_list **tokens);
int		get_start(char *str);
void	add_fake_cmd(t_list **tokens, int cmd);
char	*here_doc_name(char *common, int nbr);
void	lexer_err(char *str);
char	*expand_input(t_env *env, char *line);
char	*expand(t_env *env, char *line);

void	display_tokens(t_list	*tokens);
// wildcards
char	*iswildcards(char *input, char	*ini_s);
char	double_or_single(char input, char old_c);
int		isendwith(char *string);
void	fre_tab(char **pp); // this maybe deleted
// char	*add_wildcards_to_input(char *input, char *tmp);
char	*local_dir(char *tmp);
int		is_spaced_double_single(char *str);
char	*get_initial_token(char *str);
int		input_arg_size(char *str);
#endif