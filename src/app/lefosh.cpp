#include "lefosh.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char user[USER_MAX];
char hostname[HOSTNAME_MAX];
char workdir[WORKDIR_MAX];

void shell_loop(void) {

    initialize_shell();

    char* input;
    char** args;
    bool status = true;

    do {
        print_shell_prompt();
        input = shell_read(); if (strncmp(input, "", strnlen(input, INPUT_MAX_SIZE)) == 0) continue;
        args = shell_split_args(input);
        status = shell_exec(args);

        free(input);
        free(args);
    } while(status);
}


char* shell_read(void) {
    char* input = (char*)malloc(sizeof(char) * INPUT_MAX_SIZE);

    if (!input) {
        perror("[!] shell_read\n\t-- Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    int c;
    int pos=0;
    bool prev_space = false;
    while (true) {
        c = fgetc(stdin);
        if (c == EOF || c == '\n' || pos == INPUT_MAX_SIZE) {
            if (pos == INPUT_MAX_SIZE && (c != EOF || c != '\n')) { //if reached end of input buffer but stdin is not empty, clean it
                while (true) {
                    if (c == EOF || c == '\n')
                        break;
                    c = getchar();
                }
            }
            if (input[pos-1] == ' ') {
                input[pos-1] = '\0';
                break;
            }
            input[pos] = '\0';
            break;
        }
        else {  //input sanitization: do not store sequences of spaces among arguments, eg "ls   -la" = "ls -la"
            if (c == ' ' && !prev_space) {
                input[pos] = c;
                prev_space = true;
                pos++;
                continue;
            } else if (c == ' ' && prev_space) {
                continue;
            } 
            prev_space = false;
            input[pos] = c;
        }
        pos++;
    }
    return input;
}

char** shell_split_args(char* input) {
    int bufsize = NUM_ARGS;
    char **args = (char**)malloc(NUM_ARGS * sizeof(char*));
    char *token = strtok(input, TOKEN_DELIMITER);
    if (token == NULL) {
        perror("[!] shell_split_args\n\t-- Error: could not get first argument");
        exit(EXIT_FAILURE);
    }
    
    unsigned int i=0;
    while (token != NULL) {
        args[i] = token;
        i++;
        if (i >= bufsize) {
            bufsize = bufsize * 2;
            args = (char**)realloc(args, bufsize * sizeof(char*));
            if (args == NULL) {
                perror("[!] shell_split_args\n\t-- Error: could not allocate more space for the args buffer");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIMITER);
    }
    args[i] = NULL;

    return args;
}

bool shell_exec(char** args) {
    return shell_launch(args);
}


int shell_launch(char** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) { //then we are in the child proc
        if (execvp(args[0], args) == -1) {
            perror("[!] shell_launch\n\t-- Error: execvp returned -1");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {  //parnet process
        perror("[!] shell_launch\n\t-- Error: fork failed");
    } else {  //parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);  //waits for a specific pid to change state
        } while (wpid == 0);  // or do while !WIFEXITED(status) && !WIFSIGNALED(status)
        // wait(NULL);  //this works as well, waits for any child process to terminate
      
    }

    return 1;
}

void initialize_shell() {
    char* tmpuser = getlogin();
    if (tmpuser == NULL) {
        perror("[!] initialize_shell\n\t-- Error: could not get user");
        exit(EXIT_FAILURE);
    }
    strncpy(user, tmpuser, USER_MAX);  //get user
    gethostname(hostname, HOSTNAME_MAX);  //get user
    if (hostname == NULL) {
        perror("[!] initialize_shell\n\t-- Error: could not get hostname");
        exit(EXIT_FAILURE);   
    }
    if (getcwd(workdir, WORKDIR_MAX) == NULL) {
        perror("[!] initialize_shell\n\t-- Error: could not get working dir");
        exit(EXIT_FAILURE);
    }
}

void print_shell_prompt() { 
    if (user == NULL || hostname == NULL || workdir == NULL) {
        perror("[!] initialize_shell\n\t-- Error: cannot print shell prompt");
        exit(EXIT_FAILURE);
    }
    printf(COL_GRN "%s@%s",user, hostname);
    printf(COL_RESET ":");
    printf(COL_BLU "%s", workdir);
    printf(COL_RESET "$ ");
}