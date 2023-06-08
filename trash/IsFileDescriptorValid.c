/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsFileDescriptorValid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:12:52 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/02 18:13:22 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include #include <fcntl.h>

int	isFileDescriptorValid(int fd)
{
    return fcntl(fd, F_GETFD) != -1;
}