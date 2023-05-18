#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	// char **argv = {"echo", "-n", "hello"};
	int i = 0;
	while (i++ < 40)
	{
		if (*env == NULL)
		printf("env is null\n");
		env++;
	}
	// printf("Program name: %s\n", av[0]);
	// char **argv = av + 1;
	// execve("cat.sh", argv, env);
	// perror("execve");
	return (0);
}