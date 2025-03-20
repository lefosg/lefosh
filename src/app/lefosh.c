#include "lefosh.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#define INPUT_MAX_SIZE 100


int main(int argc, char** argv) {
    
    shell_loop();

    return EXIT_SUCCESS;


}


void shell_loop(void) {

    char* input;
    char** args;
    bool status = true;

    do {
        printf("> ");
        input = shell_read();
        args = shell_split_args(input);
        // status = shell_exec(args);

        printf("\n");
        free(input);
        // free(args);
    } while(status);
}


char* shell_read(void) {
    char* input = malloc(sizeof(char) * INPUT_MAX_SIZE);

    if (!input) {
        perror("[!] shell_read\n\t-- Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    int c;
    int pos=0;
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
            input[pos] = '\0';
            break;
        }
        else {
            input[pos] = c;
        }
        pos++;
    }
    
    return input;
}

char** shell_split_args(char* input) {
    unsigned int position = 0;
    // unsigned int arg_start=;

    while (input[position] != '\0') {
        if (input[position] == ' ') {
            printf("gay");
        }

        position++;
    }


}

bool shell_exec() {

}
