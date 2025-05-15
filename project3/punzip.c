#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char *filename;
} ThreadA;


void *punzip(void *arg) {
    ThreadA *targ = (ThreadA *)arg;
    const char *filename = targ->filename;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("punzip: cannot open file\n");
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
    return NULL;
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("unzip: file1 [file2 ...]\n");
        exit(1);
    }

    int file_count = argc-1; //updates the file count
    pthread_t threads[file_count];
    ThreadA args[file_count];

    //thread for each file 
    for (int i = 0; i < file_count; i++) {
        args[i].filename = argv[i + 1];
        if (pthread_create(&threads[i], NULL, punzip, &args[i]) != 0) {
            fprintf(stderr, "unzip couldn't create thread\n");
            exit(1);
        }
    }
    for (int i = 0; i < file_count; ++i){
        pthread_join(threads[i], NULL);
    }
    return(0);
}

