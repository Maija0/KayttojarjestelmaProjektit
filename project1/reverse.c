#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT 1000 

int readAndPrint(FILE *inputFile, FILE *outputFile) {
    int count = 0; //count of lines in lines variable
    char oneLine[MAX_LENGHT];
    char **lines;
    int n = 10; //base size for file name/line 

    lines = (char **)calloc(n, sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    while (fgets(oneLine, sizeof(oneLine), inputFile)) { // reads lines from input.txt and stores to oneline
        oneLine[strcspn(oneLine, "\n")] = 0; //remove newline
        if(count >= n) {
            n *= 2;
            lines = realloc(lines, n * sizeof(char *));
                if (lines == NULL) {
                fprintf(stderr, "malloc failed2\n");
                exit(1);
            }
        }
        
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
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        FILE *inputFile = fopen(argv[1], "r");

        if (inputFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return(1);
        }
        FILE *outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            return(1);
        }
        readAndPrint(inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }   else    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return(1);
       
    }
    return(0);
}

