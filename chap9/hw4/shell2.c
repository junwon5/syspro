#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 128

int main() {
    char buf[MAXLINE];
    char *args[MAXARG];
    char *saveptr;
    pid_t pid;
    int status, background;
    int i;

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(buf, MAXLINE, stdin) == NULL) break;
        if (buf[0] == '\n') continue;

        // 개행 문자 제거
        buf[strcspn(buf, "\n")] = 0;

        // strtok_r을 이용해 공백 단위로 인자 분리
        i = 0;
        char *token = strtok_r(buf, " ", &saveptr);
        while (token != NULL) {
            args[i++] = token;
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) {
            printf("Exit\n");
            break;
        }

        // 후면(&) 처리 확인
        background = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL; // & 기호 제거
        }

        printf("[%d] Parent process start\n", getpid());
        
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            continue;
        }

        if (pid == 0) { // 자식 프로세스
            execvp(args[0], args);
            fprintf(stderr, "%s: execution failed\n", args[0]);
            exit(1);
        } else { // 부모 프로세스
            if (!background) {
                waitpid(pid, &status, 0);
                printf("Parent process end\n");
            } else {
                printf("[%d] child process start\n", pid);
            }
        }
        printf("SUCCESS\n");
    }
    return 0;
}
