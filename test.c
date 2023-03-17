#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv, char **env)
{
    printf("%s\n", getenv(argv[1]));
    return (0);
}
