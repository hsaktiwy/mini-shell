/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:44 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/02 15:03:24 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// parser
t_list	*parser(t_env *env, t_list **tokens, char *input);
int		redirection_habdling(t_env *env, t_list **tokens);
int		check_piping(char *input);
void	printf_error_redi(t_list *list);

int		printf_error(int boolean);
//		redirection parte
int		out_append_red(t_file *tmp, int out_app);
void	syntax_error_here_doc(t_list **tokens);
int		here_doc_red(t_env *env, t_file *tmp);
int		heredoc(t_env *env, char *delimiter, int h_fd, int exp);
int		in_redirection(t_file *tmp);
int		find_delimeter(char *line, char *needle);
int		in_red_cmd(t_env *env, t_token **red, t_token **command);
#endif