#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("parental process start\n");
    
    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "first failed");
        exit(1);
    }
    if (fork() == 0) {
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "second failed");
        exit(2);
    }
    if (fork() == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "third failed");
        exit(3);
    }

    // 자식 프로세스들이 모두 끝날 때까지 대기
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("parental process end\n");
}
