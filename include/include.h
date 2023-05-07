/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:58:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 14:57:13 by hsaktiwy         ###   ########.fr       */
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

//list 
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin(char *s1, char *s2);
void	ft_lstadd_front(t_list **lst, t_list *new);\
void	ft_lstadd_in_index(t_list **list, t_list *new, int index);
void	ft_lstdelete_index(t_list **list, int index);
void	ft_lstfree_node(t_list **node);
// helper to check input

char	*get_single_quote(char *s, int *index);
char	*get_double_quote(char *s, int *index);
char	*get_simple_arg(char *str, int *index);
char	*expand_env_var(char *s, char *res,int k);
int		check_quotes_validity(char *input);
t_file	*get_file(char *input, int *index);
t_cmd	*get_cmd(char *input, int *index);
// split
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_realloc(void *ptr, size_t size);
void	ft_strncat(char *s1, const char *s2, size_t n);
// character checker
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		iswhitespace(char c);
<<<<<<< HEAD
int		str_iswhitespaced(char *str);
=======

<<<<<<< HEAD
//
int	ft_strcmp(const char *s1, const char *s2);
=======
>>>>>>> 88b3d092ed7088f038f8c2081b63bcc5d2f77326
// get next line 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
char	*get_next_line(int fd);
size_t	ft_strlen_nln(char *str);
void	*ft_calloc(size_t count);
void	clean(char *s);
void	*free_rest(char **rest);
>>>>>>> fa09970a2a678018264e0dcf64f33c4584a4f238

#endif