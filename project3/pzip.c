// https://www.geeksforgeeks.org/posix-threads-in-os/ 
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html Lists all <phtread.h> functions such as join, create thread ...
// https://en.wikipedia.org/wiki/Pthreads
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char *filename;
} ThreadA;

void *pzip(void *arg) {
    ThreadA *targ = (ThreadA *)arg;
    const char *filename = targ->filename;
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("pzip: cannot open file\n");
        exit(1);
    }
    char current, prev;
    int count = 1;

    prev = fgetc(file);
    if (prev == EOF) {
        fclose(file);
        return NULL;
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
        printf("pzip: file1 [file2 ...]\n");
        exit(1);
    }
    int file_count = argc-1; //updates the file count
    pthread_t threads[file_count];
    ThreadA args[file_count];

    //thread for each file 
    for (int i = 0; i < file_count; i++) {
        args[i].filename = argv[i + 1];
        if (pthread_create(&threads[i], NULL, pzip, &args[i]) != 0) {
            fprintf(stderr, "pzip couldn't create thread\n");
            exit(1);
        }
    }
    for (int i = 0; i < file_count; ++i){
        pthread_join(threads[i], NULL);
    }
    return(0);
}