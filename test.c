#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	char *p;
	p = NULL;

	while (*p)
		;
	// int fd = open("out", O_RDWR); //3
	// dup2(fd, STDOUT_FILENO);
	// close(fd);
	// int fd2 = open("cat.sh", O_RDWR);
	// printf("fd = %d fd2 = %d\n", fd, fd2);
	// if (isatty(1))
	// 	write(1, "Is a tty\n", 9);
	// else
	// 	write(1, "NOt a tty\n", 10);

	// char **argv = {"echo", "-n", "hello"};
	// int i = 0;
	// while (i++ < 40)
	// {
	// 	if (*env == NULL)
	// 	printf("env is null\n");
	// 	env++;
	// }
	// printf("Program name: %s\n", av[0]);
	// char **argv = av + 1;
	// execve("cat.sh", argv, env);
	// perror("execve");
	return (0);
}