#ifndef ENVIRONEMENT_H
# define ENVIRONEMENT_H

# include "../libft/libft.h"
# include "../exception/exception.h"

// envirement variable
typedef struct s_holder
{
	char	*key;
	char	*value;
}	t_holder;

typedef struct s_env
{
	t_list	*l_env;
	char 	**env;
}	t_env;

// function that initialize the t_env from env
t_env		*ft_init_env(char **env);
t_list		*ft_lst_list_holder(char **env);
t_holder	*ft_lstnewholder(char *str);
// function that set value to t_env from user
// function that replace value from key in t_env with new one
void		ft_setenv(t_env **env, char *key, char *value);
// function that get value of a special key
char		*ft_getenv(t_env *env, char *key);
#endif