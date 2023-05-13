#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int id = fork();
	if (id == 0)
	{
		execve(cmd[0], cmd, env);
	
	}
	wait(0);
	return (0);
}