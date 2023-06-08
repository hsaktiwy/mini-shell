/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_t_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:47:47 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/08 17:12:29 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	display_ambiguise(t_file	*tmp)
{
	write(STDERR_FILENO, "minishell : ", 12);
	write(STDERR_FILENO, tmp->token_file,
		ft_strlen(tmp->token_file));
	write(STDERR_FILENO, ": ambiguous redirect\n", 21);
}
