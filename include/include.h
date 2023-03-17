/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:58:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 15:59:38 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdlib.h>
# include "exception/exception.h"
typedef enum arg_type{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VARIABLE
}t_argument_type;

typedef struct	list
{
	void		    *content;
	struct list     *next;	
}t_list;

typedef struct argument
{
    t_argument_type arg_type;
    char			**args;
}t_arguments;

typedef struct file
{
    t_argument_type arg_type;
    char			*a_file;
}t_file;

typedef struct command
{
	char			*cmd;
    t_arguments     *arg;
	int				cmd_in;
	int				cmd_out;	
}t_cmd;

//list 
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin(char *s1, char *s2);

// helper to check input
int	    iswhitespace(char c);
char	*next_arg(char *str, int *index);

// split
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// character checker
int	ft_isdigit(int c);
int	ft_isalpha(int c);
#endif