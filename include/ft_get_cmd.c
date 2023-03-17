/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:07:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/15 19:17:33 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_cmd	*get_cmd(char *input, int *index)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	if (!input[i])
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (input[i] == '\'')
		cmd->arg_type = SINGLE_QUOTE;
	else if (input[i] == '\"')
		cmd->arg_type = DOUBLE_QUOTE;
	else
				
}