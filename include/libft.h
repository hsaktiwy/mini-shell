/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:29:04 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/14 12:38:20 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

//list
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin(char *s1, char *s2);
void	ft_lstdelete_index(t_list **list, int index, void (*del)(t_list **));

// split
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_realloc(void *ptr, size_t size);
void	ft_strncat(char *s1, const char *s2, size_t n);
char	**ft_t_strdup(char **str, size_t size);
int		ft_t_strlen(char **str);
// character checker
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		iswhitespace(char c);
int		str_iswhitespaced(char *str);
int		surpace_whitesspaces(char *str, int *index);
char	*ft_strstr(const char *haystack, const char *needle);
//
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*str_join(char *s1, char *s2);
int		ft_atoi(const char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_replace(void *str, char old, char new);
void	free_tab(char **pp);
// get next line 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);

#endif
