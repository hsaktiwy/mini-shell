/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:02:18 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 20:26:13 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTERS_H
# define STRUCTERS_H

# include "libft.h" 

typedef enum types{
	COMMAND,
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HERE_DOC,
	APPEND_REDIRECT,
}t_token_type;

// envirement variable
typedef struct s_holder
{
	char	*key;
	char	*value;
}	t_holder;

typedef struct s_env
{
	t_list	*l_env;
	char	**env;
}	t_env;

// tokens 
typedef struct s_token
{
	t_token_type	type;
	void			*value;	
}t_token;

// structs used in execute.c for norminette
typedef struct s_fd
{
	int	fd[2];
	int	old_fd;
}	t_fd;

typedef struct s_execve_params
{
	char	*path;
	char	**args;
}	t_execve_params;

// lexing
typedef enum s_arg_type{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VARIABLE
}	t_argument_type;

typedef struct s_file
{
	char			*a_file;
	char			*token_file;
	int				here_doc_exp;
}t_file;

typedef struct s_command
{
	char			*cmd;
	t_list			*arg;
	size_t			arg_count;
	int				cmd_in;
	int				cmd_out;
	char			*file_in;
	char			*file_out;
	int				error;
}t_cmd;

#endif