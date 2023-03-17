/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:11 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 10:31:13 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	executer(char *input)
{
	t_list	*tokens;
	int		err_lex;
	
	tokens = NULL;
	err_lex = lexer(&tokens, input);
}