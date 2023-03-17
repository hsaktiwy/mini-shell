/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excep1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:12:52 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/16 10:19:58 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.h"

void	error(void)
{
	printf("\33[31mmini_shell : \33[00m");
}

void	no_mem(void)
{
	error();
	printf("\33[33mCannot allocate memory\33[00m\n");
}
