#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(const char *term, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-grep: cannot open file\n");
        exit(1);
    }
    char line[3000]; //max line size
    while(fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, term) != NULL) {
            printf("%s", line); //print the line with the term in it
        }
    }
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc == 1) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    const char *term = argv[1]; // the term we are locating
    const char *filename = argv[2]; // where we are looking to find the term
    grep(term, filename);

    return(0);
}