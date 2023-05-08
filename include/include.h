/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:58:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 15:01:25 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdlib.h>
# include <unistd.h>
# include "exception/exception.h"
typedef enum s_arg_type{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VARIABLE
}t_argument_type;

typedef struct	s_list
{
	void		    *content;
	struct s_list     *next;	
}t_list;

typedef struct s_argument
{
    t_argument_type arg_type;
    char			**args;
}t_arguments;

typedef struct s_file
{
	t_argument_type arg_type;
    char			*a_file;
}t_file;

typedef struct s_command
{
	char			*cmd;
	t_list			*arg;
	size_t			arg_count;
	int				cmd_in;
	int				cmd_out;	
}t_cmd;

void	ft_lstfree_node(t_list **node);
char	*get_single_quote(char *s, int *index);
char	*get_double_quote(char *s, int *index);
char	*get_simple_arg(char *str, int *index);
char	*expand_env_var(char *s, char *res,int k);
int		check_quotes_validity(char *input);
t_file	*get_file(char *input, int *index);
t_cmd	*get_cmd(char *input, int *index);
#endif