#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	// char **argv = {"echo", "-n", "hello"};

	char **argv = av + 1;
	execve("/bin/ls", argv, env);
	perror("execve");
	return (0);
}