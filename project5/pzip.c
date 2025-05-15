// https://www.geeksforgeeks.org/posix-threads-in-os/ 
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html Lists all <phtread.h> functions such as join, create thread ...
// https://en.wikipedia.org/wiki/Pthreads
// https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/ I followed the example and surrounded the sections that could cause issues with lock/unlock

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char *filename; // Threads filename
} ThreadA;

pthread_mutex_t lock;  //Mutex used to sync stdout

// This function compresses a file 
void *pzip(void *arg) {
    ThreadA *targ = (ThreadA *)arg;
    FILE *file = fopen(targ->filename, "r");
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
            pthread_mutex_lock(&lock); // This locks access so that no other thread can access this part of the code
            fwrite(&count, sizeof(int), 1, stdout); // use fwrite and write count as 4byte integer
            fwrite(&prev, sizeof(char), 1, stdout); // write the char
            pthread_mutex_unlock(&lock); // Release the lock
            prev = current;
            count = 1;
        }
    }
    //writes the last bytes
    pthread_mutex_lock(&lock);
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&prev, sizeof(char), 1, stdout);
    pthread_mutex_unlock(&lock);
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("pzip: file1 [file2 ...]\n");
        exit(1);
    }
    // Updates the file count so that it can be used below in creating threads
    int file_count = argc-1;
    pthread_t threads[file_count];
    ThreadA args[file_count];

    // Create thread for each given file
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
    pthread_mutex_destroy(&lock);
    return(0);
}