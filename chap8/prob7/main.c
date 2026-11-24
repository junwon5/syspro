#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int opt;

    if (argc < 2) {
        printf("사용법: %s [-e [환경변수명]] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "e::ugip")) != -1) {
        switch (opt) {
            case 'e':
                if (optarg) {
                    char *val = getenv(optarg);
                    if (val) {
                        printf("%s = %s\n", optarg, val);
                    } else {
                        printf("환경변수 %s를 찾을 수 없습니다.\n", optarg);
                    }
                } else if (optind < argc && argv[optind][0] != '-') {
                    char *val = getenv(argv[optind]);
                    if (val) {
                        printf("%s = %s\n", argv[optind], val);
                    } else {
                        printf("환경변수 %s를 찾을 수 없습니다.\n", argv[optind]);
                    }
                    optind++;
                } else {
                    for (char **env = environ; *env != NULL; env++) {
                        printf("%s\n", *env);
                    }
                }
                break;

            case 'u':
                printf("나의 실제 사용자 ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
                printf("나의 유효 사용자 ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
                break;

            case 'g':
                printf("나의 실제 그룹 ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
                printf("나의 유효 그룹 ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
                break;

            case 'i':
                printf("나의 프로세스 번호 : [%d]\n", getpid());
                break;

            case 'p':
                printf("내 부모 프로세스 번호 : [%d]\n", getppid());
                break;

            default:
                break;
        }
    }

    return 0;
}
