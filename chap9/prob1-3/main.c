#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pid;
    pid = fork();
    if (pid == 0) {
        sleep(1);
        printf("[Child] : Hello, world pid=%d\n", getpid());
    }
    else {
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }
}
