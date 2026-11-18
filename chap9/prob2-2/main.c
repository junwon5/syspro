#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid1, pid2, child, status;

    printf("[%d] Parent process start \n", getpid());

    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] First child process start \n", getpid());
        sleep(2);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] Second child process start \n", getpid());
        sleep(1);
        exit(2);
    }

    child = waitpid(pid1, &status, 0);
    printf("[%d] First child process %d end \n", getpid(), child);
    printf("\tExit code %d\n", status >> 8);

    printf("[%d] Parent process end \n", getpid());
}
