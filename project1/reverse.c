#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT 1000 
// argc numbers of arguments, argv array of arguments, argv[0] = ./reverse and argv[1] is input.txt

int readAndPrint(FILE *inputFile, FILE *outputFile) {
    char oneLine[MAX_LENGHT];
    while (fgets(oneLine, sizeof(oneLine), inputFile)) {
        fprintf(stdout, "%s", oneLine);
    }
}
int main (int argc, char *argv[]) {
    if (argc == 2) {
        FILE *inputFile = fopen(argv[1], "r");

        if (inputFile == NULL) {
            fprintf(stderr, "error when opening inputfile '%s'\n", argv[1]);
            return(1);
        }
        readAndPrint(inputFile, stdout);
        fclose(inputFile);
    }
    printf("\n");
    return(0);
}

