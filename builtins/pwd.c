/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/24 14:50:03 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *command)
{
	char	cwd[4096];

	getcwd(cwd, 4096);
	write(command->cmd_out, &cwd, ft_strlen(cwd));
	write(command->cmd_out, "\n", 1);
	return (0);
}