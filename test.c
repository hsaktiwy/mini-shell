#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv, char **env)
{
    //printf("%s\n", getenv(argv[1]));
    char c;
    while (1)
    {
        read(STDIN_FILENO, &c, 1);
        write(STDOUT_FILENO, &c, 1);
    }
    return (0);
}
