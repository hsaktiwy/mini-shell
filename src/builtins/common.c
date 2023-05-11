/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:45:11 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/11 19:28:59 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_key(char *key)
{
	size_t	i;

	if (key && !((key[0] >= 'a' && key[0] <= 'z') ||
			(key[0] >= 'A' && key[0] <= 'Z')) && key[0] != '_')
		return (1);
	i = 1;
	while(key[i])
	{
		if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z') ||
				(key[i] >= '0' && key[i] <= '9') || key[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int print_error2(char *identifier)
{
	write(2, "minishell: export: `", 21);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}
