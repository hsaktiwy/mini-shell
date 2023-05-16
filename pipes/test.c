/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:05:43 by aigounad          #+#    #+#             */
/*   Updated: 2023/05/14 18:53:04 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	pid_t id1;
	int fd[2];
	char buffer[100];

	if (pipe(fd) != 0)
		perror("pipe");
	id1 = fork();
	if (id1 < 0)
		perror("fork");
	if (id1 == 0)
	{
		close(fd[1]);
		read(fd[0], buffer, 14);
		close(fd[0]);
		printf("buffer = %s", buffer);
	}
	else
	{
		// close read end of pipe
		close(fd[0]);
		write(fd[1], "helloworld!\n", 13);
		close(fd[1]);
		wait(NULL);
	}
	
}
