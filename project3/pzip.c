#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zip( const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-zip: cannot open file\n");
        exit(1);
    }
    char current, prev;
    int count = 1;

    prev = fgetc(file);
    if (prev ==EOF) {
        fclose(file);
        return;
    }
    while ((current = fgetc(file)) != EOF) {
        if (current == prev) { //adds count until letter changes
            count++;
        } else { // letter changed so write the combination
            fwrite(&count, sizeof(int), 1, stdout); // use fwrite and write count as 4byte integer
            fwrite(&prev, sizeof(char), 1, stdout); // write the char
            prev = current;
            count = 1;
        }
    }
    //writes the last bytes
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&prev, sizeof(char), 1, stdout);
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i<argc; i++) {
        zip(argv[i]);
    }

    return(0);
}