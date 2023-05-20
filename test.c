#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

char *global(char *env)
{
	static char *g;

	if (env == NULL)
		return g;
	else
		g = env;
	return g;
}

void	ft_change_p()
{
	char *p = global(NULL);
	p[0] = 'H';
	p[1] = 'E';
	p[2] = 'L';
	p[3] = 'L';
	p[4] = 'O';
	p[5] = 0;
}
int	main(int ac, char **av, char **env)
{
	// char p[100];
	// global(p);

	// ft_change_p();

	// printf("p = [%s]", p);
	while (1)
	{
		printf("333333333333333\n");
		sleep(1);
	}
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