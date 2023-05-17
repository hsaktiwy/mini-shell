/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:13:17 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/13 16:46:45 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_H
# define EXCEPTION_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
// # include "../include.h"

void	error(void);
void	no_mem(void);
void	lexer_err(char *str);
void	ft_perror(char *msg);
#endif