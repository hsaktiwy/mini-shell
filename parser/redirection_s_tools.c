/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_s_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:12:29 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/27 15:12:59 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_delimeter(char *line, char *needle)
{
	int	i;

	i = 0;
	if (!(*needle) && *line == '\n')
		return (1);
	while (line[i] && needle[i] && needle[i] == line[i])
		i++;
	if (line[i] == '\0' && !needle[i])
		return (1);
	return (0);
}
