// a simple shell written in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64


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
            perror("readline: getline failed");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

int parse_line(char *line, command *cmd){

    int buffersize = MAX_ARGS;
    int pos = 0;

    char **tokens = malloc(MAX_ARGS * sizeof(char*));
    char *token = strtok(line, " \t\n\r\a");

    if (token == NULL) {
        perror("parse_line: memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while (token != NULL) {
        tokens[pos++] = token;
        
        if (pos >= buffersize) {
            buffersize += MAX_ARGS;
            tokens = realloc(tokens, buffersize * sizeof(char*));

            if (tokens == NULL) {
                perror("parse_line: memory allocation failed");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n\r\a");
    }

    tokens[pos] = NULL;

    if (pos == 0) {
        free(tokens);
        perror("parse_line: no command entered");
        return 0;
    }

    cmd->name = tokens[0];
    cmd->args = tokens;
    cmd->argc = pos;

    return 1;

}

int execute(command cmd) {
    if (strcmp(cmd.name, "exit") == 0) {
        return 0;
    }

    __pid_t pid = fork();
    if (pid == -1) {
        perror("execute: fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(cmd.name, cmd.args) == -1) {
            perror("execute: execvp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }

    return 1;
}

int main(int argc, char **argv) {

    int status = 1;
    command cmd;

    char *line = NULL;

    while (status) {
        
        printf("yass > ");
        line = read_line();
        
        // test if line is read correctly
        // printf("%s", line); 

        if (parse_line(line, &cmd)) {

            // test if command is parsed correctly
            // printf("Cmd: %s\n", cmd.name);
            // printf("Args: ");
            // for (int i = 1; i < cmd.argc; i++) {
            //     printf("%s ", cmd.args[i]);
            // }
            // printf("\n");

            status = execute(cmd);
            free(cmd.args);
        }

    }

    free(line);

    return 0;
}