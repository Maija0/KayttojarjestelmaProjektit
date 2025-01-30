#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 1000 
// argc numbers of arguments, argv array of arguments, argv[0] = ./reverse and argv[1] is input.txt

int main (int argc, char *argv[]) {

    FILE *inputFile = fopen(argv[1], "r");
    char oneLine[MAX_LENGHT];
    while (fgets(oneLine, sizeof(oneLine), inputFile)) {
        fputs(oneLine, stdout);
    }
    fclose(inputFile);
    return(0);
}

