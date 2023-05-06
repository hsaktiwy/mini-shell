#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(int arc, char **argv) {
    char* line;

    line = readline("Enter a line: ");

    printf("Line: %s", line);

    free(line);

    return 0;
}
