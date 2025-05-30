#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Decompresses a rle file by reading count and character and giving correct output
void unzip( const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-unzip: cannot open file\n");
        exit(1);
    }
    int count;
    char character;
    while(fread(&count, sizeof(int), 1, file) == 1) { // converts 4byte binary back to integer
        fread(&character, sizeof(char), 1, file);   //reads the character and
        for (int i = 0; i < count; i++) { //Writes the character count-times
            putchar(character); 
        }
    }
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i<argc; i++) {
        unzip(argv[i]);
    }
    return(0);
}