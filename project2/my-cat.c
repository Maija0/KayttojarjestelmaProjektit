#include <stdio.h>
#include <stdlib.h>

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("my-cat: cannot open file\n");
        exit(1);
    }
    char line[3000];
    while(fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("less than 2 arguments\n");
        return(0);
    }   else if (argc ==2) {
        printf("Two arguments were given\n");
    }
    for (int i = 1; i < argc; ++i) {
        if (i != 1) {
            printf("\n");
        }
        print_file(argv[i]);
    }
    printf("\n");
    return(0);
}