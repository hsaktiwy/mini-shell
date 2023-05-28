/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:20 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/25 16:00:09 by aigounad         ###   ########.fr       */
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
