// 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// volatile sig_atomic_t interrupted = 0;

// void sigintHandler(int signum) {
//     interrupted = 1;
// }

<<<<<<< HEAD
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
=======
int main() {
    // signal(SIGINT, sigintHandler);

    // char buffer[256];
    // printf("Enter heredoc contents (press Ctrl+D to finish):\n");
>>>>>>> main

    // while (1) {
    //     if (fgets(buffer, sizeof(buffer), stdin) == NULL || interrupted) {
    //         // Check if EOF or SIGINT received
    //         printf("Heredoc interrupted.\n");
    //         break;
    //     }
    //     // Process the heredoc contents
    //     printf("Received: %s", buffer);
    // }
	// close(STDIN_FILENO);
	// write(0, "sd\n", 3);
	// while(1);

    char *p = malloc(100);

    pid_t id = fork();
    if (id == 0)
    {
        // free(p);
        printf("Hello from child\n");
        exit(0);
    }
    // pid_t id2 = fork();
    // if (id2 == 0)
    // {
    //     printf("Hello from child2\n");
    //     exit(0);
    // }
    wait(NULL);
    wait(NULL);
    printf("Hello from parent\n");
    // free(p);
    return 0;
}
