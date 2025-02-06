#include <stdio.h>
#include <stdlib.h>

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-cat: cannot open file\n");
        exit(1);
    }
    char line[3000];
    while(fgets(line, sizeof(line), file) != NULL) { // read lines with fgets until NULL/EOF
        printf("%s", line); //print out a line
    }
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) { // return if less than two arguments
        return(0);
    }
    for (int i = 1; i < argc; ++i) { // loop that goes until all the arguments (filenames) have been printed
        if (i != 1) { // at the start of new print_file call, add a newline to separate file lines
            printf("\n");
        }
        print_file(argv[i]); // call print_file on current file
    }
    printf("\n");
    return(0);
}