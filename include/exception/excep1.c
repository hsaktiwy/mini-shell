/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excep1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:12:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/13 16:46:39 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.h"

void	put_string(char *str)
{
	write(STDERR_FILENO, str,ft_strlen(str));
}

void	error(void)
{
	put_string("\33[31mmini_shell : \33[00m");
}

void	no_mem(void)
{
	error();
	put_string("\33[33mCannot allocate memory\33[00m\n");
}

void	lexer_err(char *str)
{
	put_string("\33[33mParse Error near: \33[00m\33[30m");
	put_string(str);
	put_string("\33[00m\n");
}

void	ft_perror(char *msg)
{
	perror(msg);
	exit(1);
}
