#include <stdio.h>
#include <string.h>

#define MAXLINES 100
#define MAXLEN 1000

void copy(char from[], char to[]);

int main() {
    char lines[MAXLINES][MAXLEN];
    char temp[MAXLEN];
    int count = 0;

    while (count < MAXLINES && fgets(lines[count], MAXLEN, stdin) != NULL) {
        size_t len = strlen(lines[count]);
        if (len > 0 && lines[count][len - 1] == '\n') {
            lines[count][len - 1] = '\0';
        }
        if (strlen(lines[count]) == 0) break;
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strlen(lines[j]) < strlen(lines[j + 1])) {
                copy(lines[j], temp);
                copy(lines[j + 1], lines[j]);
                copy(temp, lines[j + 1]);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
