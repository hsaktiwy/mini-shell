/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:58:09 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 19:27:47 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

//includes
# include "libft/libft.h"
# include "exception/exception.h"
# include "environement/environement.h"

//structs
typedef enum s_arg_type{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VARIABLE
}	t_argument_type;

typedef struct s_argument
{
    t_argument_type arg_type;
    char			**args;
}t_arguments;

typedef struct s_file
{
	t_argument_type arg_type;
    char			*a_file;
	char			*token_file;
}t_file;

typedef struct s_command
{
	char			*cmd;
	t_argument_type cmd_type;
	t_list			*arg;
	size_t			arg_count;
	int				cmd_in;
	int				cmd_out;
	char			*file_in;
	char			*file_out;
	t_env			*env;
}t_cmd;

// global variable
extern int	g_exit_status;

// helper to check input
void	ft_lstfree_t_file(t_list **node);
char	*get_token(char *str);
char	*get_single_quote(t_env *env, char *s, int *index);
char	*get_double_quote(t_env *env, char *s, int *index);
char	*get_simple_arg(t_env *env, char *str, int *index);
char	*expand_env_var(t_env *env, char *s, char *res,int k);
int		check_quotes_validity(char *input);
int		is_splitable_env(char *str);
t_file	*get_file(t_env *env, char *input, int *index);
t_cmd	*get_cmd(t_env *env, char *input, int *index);
t_file	*creat_arg(char *file_name, t_argument_type type);
t_cmd	*ini_cmd(t_env *env);
#endif
