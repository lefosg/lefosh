#ifndef LEFOSH_H
#define LEFOSH_H

#include <stdbool.h>

#define INPUT_MAX_SIZE 100
#define NUM_ARGS 10
#define TOKEN_DELIMITER " "

#define USER_MAX 100
#define HOSTNAME_MAX 100
#define WORKDIR_MAX 255  //could check against filesystem

#define COL_GRN   "\x1B[32m"
#define COL_WHT   "\x1B[37m"
#define COL_BLU   "\x1B[34m"
#define COL_RESET "\x1B[0m"

extern char user[USER_MAX];
extern char hostname[HOSTNAME_MAX];
extern char workdir[WORKDIR_MAX];

/**
 * Shell is an infinite loop that reads, parses the arguments, and executes the command
 * This function implements this infinite loop
 */
void shell_loop(void);

/**
 * Reads input from the terminal
 * @returns a char* to a malloc'd area which contains the user input
 */
char* shell_read(void);


/**
 * Splits the arguments, one by one in an 'array of pointers'
 * @param input from the shell_read function
 * @returns an 'array of pointers' to the arguments
 */
char** shell_split_args(char* input);

/**
 * Executes the command, but includes some logic to execute builtins as well.
 * The function that really spawn the new process is shell_launch
 * @returns true or false if execution was successful or not
 */
bool shell_exec(char** args);

/**
 * Spawns a new process from the terminal
 * @param args - arguments retrieved from shell_split_args
 */
int shell_launch(char** args);

/**
 * Initializes shell with different variables and configurations
 */
void initialize_shell(void);

/**
 * Prints the shell prompt, which is sth like user@machine_name:hostname$ (bash like prompt)
 */
void print_shell_prompt(void);







#endif