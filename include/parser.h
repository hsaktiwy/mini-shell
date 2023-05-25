/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:44 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 14:37:48 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include "minishell.h"

// parser
t_list	*parser(t_env *env, t_list **tokens, char *input);
int		redirection_habdling(t_env *env, t_list **tokens);
//		redirection parte
int		out_append_red(t_file *tmp, int out_app);
int		here_doc_red(t_env *env, t_file *tmp);
int		heredoc(t_env *env, char *delimiter, int h_fd);
int		in_redirection(t_file *tmp);
int		find_delimeter(char *line, char *needle);
#endif