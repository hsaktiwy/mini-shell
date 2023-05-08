#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
char	*get_next_line(int fd);
size_t	ft_strlen_nln(char *str);
void	*ft_calloc(size_t count);
void	clean(char *s);
void	*free_rest(char **rest);

#endif