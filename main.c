/*
 * Utility gets .so file path and its CRC32 sum. Then checks
 * CRC32 of the library file and open it if sum is ok.
 * 
 * Using : icon <file> <CRC32_number_in_HEX_format>
 * 
 */


#include "crc32.h"
#include "libcdl.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char ** argv) {
    
    printf(">>> main\n");

    void *h = dlopen("libc.so.6", RTLD_LAZY);

    if (h == NULL) {
        printf("dlopen() error : %s\n", dlerror());
    } else {
        printf("dlopen() success!\n");
    }

    dlclose(h);

    printf("<<< main\n");

    return 0;
}