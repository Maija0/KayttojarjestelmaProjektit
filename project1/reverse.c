#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readAndPrint(FILE *inputFile, FILE *outputFile) {
    int count = 0; //count of lines in lines variable
    char *oneLine = NULL;
    char **lines;
    int n = 10;
    int j = 15;

    lines = (char **)malloc(n * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    oneLine = (char *)malloc(j * sizeof(char));

    while(1) { // do until one of the break conditions
        if (fgets(oneLine, j, inputFile) == NULL) { // read line from input, if eof break
            break;
        }
        int lineLength = strlen(oneLine);
        while (lineLength == j - 1) { // realloc memory if being one away from buffer being full
            j *= 2;
            oneLine = realloc(oneLine, j *sizeof(char)); //new memory allocated
        
            if (fgets(oneLine +lineLength, j - lineLength, inputFile) == NULL) { //important if-clause that keeps reading into oneline untill NULL is reached (end of line)
                break;
            }
            lineLength = strlen(oneLine); // update lineLength for while loop
    }
        if(count >= n) {
            n *= 2;
            lines = realloc(lines, n * sizeof(char *));
            if (lines == NULL) {
                fprintf(stderr, "realloc failed\n");
                exit(1);
            }
        }
        
        lines[count] = malloc((lineLength +1) * sizeof(char)); // allocates memory for the lenght of oneLine
        strcpy(lines[count], oneLine);
        count ++;
    }
        for(int i = count -1; i >= 0; i--) { // fprintf from last line to first line
            fprintf(outputFile, "%s", lines[i]);
            free(lines[i]); // free allocated memory throughout loop
        }
    free(lines);
    free(oneLine);
    return(0);
}


int main (int argc, char *argv[]) {
    if (argc == 1) { // Used when reversing terminal input and printing it to terminal
        readAndPrint(stdin, stdout);

    }   else if (argc == 2) { // Used when reversing input.txt to terminal
        FILE *inputFile = fopen(argv[1], "r");

        if (inputFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return(1);
        }
        readAndPrint(inputFile, stdout);
        fclose(inputFile);

    } else if (argc == 3) { // Used when reversing input.txt to output.txt
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
    }   else    { // Case: argument count different from 1, 2 or 3
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return(1);
       
    }
    return(0);
}

