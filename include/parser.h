/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:44 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/07 17:57:21 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// parser
t_list	*parser(t_list **tokens, char *input);
int		redirection_habdling(t_list **tokens);
int		check_piping(char *input);
void	printf_error_redi(t_list *list);

int		printf_error(int boolean);
//		redirection parte
int		out_append_red(t_file *tmp, int out_app);
void	syntax_error_here_doc(t_list **tokens);
int		here_doc_red(t_file *tmp);
int		heredoc(char *delimiter, int h_fd, int exp);
int		in_redirection(t_file *tmp);
int		find_delimeter(char *line, char *needle);
int		in_red_cmd(t_token **red, t_token **command);
void	get_true_file(t_file *tmp, int *num);
void	display_ambiguise(t_file	*tmp);
#endif