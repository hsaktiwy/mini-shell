/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:07:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/05 21:22:19 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_cmd	*ini_cmd()
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
	return (cmd);
}

t_cmd	*get_cmd(char *input, int *index)
{
	int		i;
	t_cmd	*cmd;
	int		stack;

	i = 0;
	if (!input)
		return (NULL);
	cmd = ini_cmd();
	if(check_quotes_validity(input))
	{
		stack = *index;
		if (input[i] && input[i] != '|')
		{
			cmd->cmd = get_simple_arg(input, index);
			if (input[i] == '$')
				cmd->cmd_type = VARIABLE;
			else
				cmd->cmd_type = WORD;
		}
		i = (*index) - stack;
	}
	return (cmd);	
}
