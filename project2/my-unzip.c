#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unzip( const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-unzip: cannot open file\n");
        exit(1);
    }

    // functionality
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i<argc; i++) {
        zip(argv[i]);
    }
    return(0);
}