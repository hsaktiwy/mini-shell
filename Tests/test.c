#include <stdio.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#define NAME "/semaphores_tes"
int main(int argc, char **argv)
{
    sem_t *sem;

    sem_unlink(NAME);
    sem = sem_open(NAME,O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED)
    {
        printf("error\n");
        exit(1);
    }
    printf("sem : %p\n", sem);
    for(int i = 0; i < 2; i++)
    {
        int id = fork();
        if (id == 0)
        {
            printf("sem_wait: %d\n",sem_wait(sem));
            printf("childe %d : waiting\n", i);
            printf("sem_post: %d\n",sem_post(sem));
            exit(0);
        }
    }
    while (wait(NULL) != -1)
        ;
    printf("all are deads\n");
    sem_wait(sem);
    printf("sem_unlink : %d\n", sem_unlink(NAME));
    printf("sem_close : %d\n",sem_close(sem));
    return (0);
}
