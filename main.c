#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

extern void *my_dlopen(const char *file, int mode);

int main(int argc, char **argv) {

    // Check arguments.
    if (argc != 3) {
        printf("Wrong arguments numbers.\n");
        exit(EXIT_FAILURE);
    }

    // argv[1] - path to lib
    // argv[2] - its checksum

    void *dlptr = my_dlopen(argv[1], RTLD_LAZY);

    if (dlptr == NULL) {
        printf("Couldn't open given library.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void *my_dlopen(const char *file, int mode) {
    void *result;

    // Check library checksum.

    result = dlopen(file, mode);
    return result;
}