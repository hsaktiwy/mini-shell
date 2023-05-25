/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:02:18 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/25 17:00:21 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTERS_H
#define STRUCTERS_H

# include "libft.h" 

typedef enum types{
	COMMAND,
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HERE_DOC,
	APPEND_REDIRECT,
}t_token_type;

// Grammar types 	// INPUT,
typedef enum g_types{
	G_COMMAND,
	S_COMMAND,
	PIPELINE,
	G_PIPE,
	REDIRECTION,
	CMD,
}t_g_types;

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
	int				here_doc_exp;
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
	int				error;
}t_cmd;

#endif