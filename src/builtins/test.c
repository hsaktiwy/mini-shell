#include <unistd.h>
#include <stdio.h>

int main() {
    if (chdir("/home") != 0) {
        perror("chdir");
    }
    return 0;
}