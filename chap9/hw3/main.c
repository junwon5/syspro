#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 1024
#define MAXARG 128

void execute_command(char *cmd) {
    char *args[MAXARG];
    char *token;
    int i = 0;
    int background = 0;
    int fd;
    char *outfile = NULL, *infile = NULL;

    // 공백 기준으로 인자 분리
    token = strtok(cmd, " \t\n");
    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            outfile = token;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            infile = token;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    // 내장 명령어 처리 (exit 등)
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0) {
        // 출력 리디렉션
        if (outfile != NULL) {
            fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0660);
            dup2(fd, 1);
            close(fd);
        }
        // 입력 리디렉션
        if (infile != NULL) {
            fd = open(infile, O_RDONLY);
            dup2(fd, 0);
            close(fd);
        }

        execvp(args[0], args);
        fprintf(stderr, "%s: execution failed\n", args[0]);
        exit(1);
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[%d] running in background\n", pid);
        }
    }
}

int main() {
    char buf[MAXLINE];
    char *commands[MAXARG];
    char *cmd;
    int i;

    while (1) {
        printf("[shell] ");
        if (fgets(buf, MAXLINE, stdin) == NULL) break;
        if (buf[0] == '\n') continue;

        // 세미콜론(;)을 기준으로 순차적 명령어 분리
        i = 0;
        cmd = strtok(buf, ";\n");
        while (cmd != NULL) {
            commands[i++] = cmd;
            cmd = strtok(NULL, ";\n");
        }
        commands[i] = NULL;

        for (int j = 0; j < i; j++) {
            execute_command(commands[j]);
        }
    }
    return 0;
}
