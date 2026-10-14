#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    for (i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &buf) < 0) {
            perror("lstat()");
            continue;
        }

        if (S_ISREG(buf.st_mode))
            printf("일반 파일\n");
        if (S_ISDIR(buf.st_mode))
            printf("디렉토리\n");
        if (S_ISCHR(buf.st_mode))
            printf("문자 장치 파일\n");
        if (S_ISBLK(buf.st_mode))
            printf("블록 장치 파일\n");
        if (S_ISFIFO(buf.st_mode))
            printf("FIFO 파일\n");
        if (S_ISLNK(buf.st_mode))
            printf("심볼릭 링크\n");
        if (S_ISSOCK(buf.st_mode))
            printf("소켓\n");
    }

    exit(0);
}
