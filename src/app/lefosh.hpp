#ifndef LEFOSH_H
#define LEFOSH_H

#include <stdbool.h>

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
 * Executes the command
 * @returns true or false if execution was successful or not
 */
bool shell_exec();









#endif