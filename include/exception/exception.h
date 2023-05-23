/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:13:17 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/23 14:20:19 by hsaktiwy         ###   ########.fr       */
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
void	put_string(char *str);
#endif