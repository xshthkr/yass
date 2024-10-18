// a simple shell written in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char **args;
    int argc;
} command;

char* read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

int main(int argc, char **argv) {

    command cmd;

    char *line = NULL;

    while (1) {
        printf("yass > ");
        line = read_line();
        printf("%s", line); // test if input is read correctly

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

    }

    free(line);

    return 0;
}