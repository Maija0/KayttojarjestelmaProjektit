// This code was done by copying pzip.c and modifying parts so the sources are same as in pzip.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char *filename; // Threads filename
} ThreadA;

pthread_mutex_t lock;  //Mutex used to sync stdout

// This function compresses a file 
void *punzip(void *arg) {
    ThreadA *targ = (ThreadA *)arg;

    FILE *file = fopen(targ->filename, "r");
    if (file == NULL) {
        printf("punzip: cannot open file\n");
        exit(1);
    }
    int count;
    char character;

    while(fread(&count, sizeof(int), 1, file) == 1) { // converts 4byte binary back to integer
        fread(&character, sizeof(char), 1, file);   //reads the character and
        pthread_mutex_lock(&lock); // This locks access so that no other thread can access this part of the code
        for (int i = 0; i < count; i++) { //Writes the character count-times
            putchar(character); 
        }
        pthread_mutex_unlock(&lock); // Release the lock
    }
    fclose(file);
    return NULL;
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("punzip: file1 [file2 ...]\n");
        exit(1);
    }
    // Updates the file count so that it can be used below in creating threads
    int file_count = argc-1;
    pthread_t threads[file_count];
    ThreadA args[file_count];

    // Create thread for each given file
    for (int i = 0; i < file_count; i++) {
        args[i].filename = argv[i + 1];
        if (pthread_create(&threads[i], NULL, punzip, &args[i]) != 0) {
            fprintf(stderr, "punzip couldn't create thread\n");
            exit(1);
        }
    }
    for (int i = 0; i < file_count; ++i){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return(0);
}

