#include "lefosh.hpp"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    // shell_loop();

    char* arg1 = (char*)malloc(sizeof(char));
    *arg1 = 'a';
    char** args = (char**)malloc(sizeof(char*)*5);
    args[0] = arg1;


    printf("%p\n", args);
    printf("%p\n", args[0]);
    printf("%c\n", *args);
    

    return 0;

 
}