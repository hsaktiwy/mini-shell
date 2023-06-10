/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:07:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 17:08:42 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->cmd_type = -1;
	cmd->cmd_in = STDIN_FILENO;
	cmd->cmd_out = STDOUT_FILENO;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->error = 0;
	return (cmd);
}
// i = 0;
// if(str[i] == '$')
// 	i++;
// else
// 	return (0);
// while (str[i] && (ft_isalnum(str[i])
// 	|| str[i] == '?' || str[i] == '_'))
// 	i++;
// if (str[i] == '\"' || str[i] == '\''
// 	|| str[i] == '$')
// 	return (0);
// else
// 	return (1); dial had is_splitable

int	is_splitable_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !iswhitespace(str[i]))
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

// t_cmd	*get_cmd(t_env *env, char *input, int *index)
// {
// 	t_cmd	*cmd;

// 	if (!input)
// 		return (NULL);
// 	cmd = ini_cmd(env);
// 	if (check_quotes_validity(input))
// 	{
// 		if (input[0] && input[0] != '|')
// 		{
// 			cmd->cmd = get_simple_arg(env, input, index);
// 			if (is_splitable_env(input))
// 				cmd->cmd_type = VARIABLE;
// 			else
// 				cmd->cmd_type = WORD;
// 		}
// 	}
// 	if (cmd->cmd == NULL)
// 		return (free(cmd), NULL);
// 	return (cmd);
// }

// t_cmd	*get_cmd(t_env *env, char *input)
// {
// 	t_cmd	*cmd;

// 	if (!input)
// 		return (NULL);
// 	cmd = ini_cmd(env);
// 	if (check_quotes_validity(input))
// 	{
// 		if (input[0] && input[0] != '|')
// 		{
// 			cmd->cmd = get_simple_arg(env, input, index);
// 			if (is_splitable_env(input))
// 				cmd->cmd_type = VARIABLE;
// 			else
// 				cmd->cmd_type = WORD;
// 		}
// 	}
// 	if (cmd->cmd == NULL)
// 		return (free(cmd), NULL);
// 	return (cmd);
// }
