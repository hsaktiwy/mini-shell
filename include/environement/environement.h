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
// function that set value to t_env from user
// function that replace value from key in t_env with new one
void		ft_setenv(t_env **env, char *key, char *value);
// function that get value of a special key
char		*ft_getenv(t_env *env, char *key);
//free
void		ft_free_env(t_env **env_t);

void		ft_unset_env_list(t_list **env_l, char *key);
void		ft_unset_env_table(char **env_table, size_t index);

// function used in unset.c
ssize_t	get_env_index(char **env_table, char *key);

t_env *global_env(t_env *env);

#endif