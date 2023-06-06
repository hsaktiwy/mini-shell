/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:15:34 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/06 19:16:07 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*reallocated_str(char *str, char *add)
{
	int		size;
	char	*res;

	size = ft_strlen(add);
	res = ft_realloc(str, ft_strlen(str) + size + 1);
	ft_strncat(res, add, size);
	return (res);
}
