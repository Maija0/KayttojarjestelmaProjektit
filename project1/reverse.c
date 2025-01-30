#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT 1000 

int readAndPrint(FILE *inputFile, FILE *outputFile) {
    char *lines[100]; 
    int count = 0;
    char oneLine[MAX_LENGHT];

    while (fgets(oneLine, sizeof(oneLine), inputFile)) { // reads lines from input.txt and stores to oneline
        oneLine[strcspn(oneLine, "\n")] = 0;

        lines[count] = malloc(strlen(oneLine)); // allocates memory for the lenght of oneLine
        strcpy(lines[count], oneLine);
        count ++;
    }
        for(int i = count -1; i >= 0; i--) { // fprintf from last line (count-1) to i >= 0 first line
            fprintf(outputFile, "%s\n", lines[i]);
            free(lines[i]); // free allocated memory throughout loop
        }
    return(0);
}


int main (int argc, char *argv[]) {
    if (argc == 1) { // ./reverse
        readAndPrint(stdin, stdout);

    }   else if (argc == 2) { // ./reverse input.txt
        FILE *inputFile = fopen(argv[1], "r");

        if (inputFile == NULL) {
            fprintf(stderr, "error when opening inputfile '%s'\n", argv[1]);
            return(1);
        }
        readAndPrint(inputFile, stdout);
        fclose(inputFile);

    } else if (argc == 3) { // ./reverse input.txt ouput.txt
        FILE *inputFile = fopen(argv[1], "r");

        if (inputFile == NULL) {
            fprintf(stderr, "error when opening inputfile '%s'\n", argv[1]);
            return(1);
        }
        FILE *outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "error when opening outputfile '%s'\n", argv[1]);
            return(1);
        }
        readAndPrint(inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }   else    {
        printf("Wrong amount of arguments. \n");
    }
    return(0);
}

