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

    dlopen("libc.so.6", RTLD_LAZY);

    printf("<<< main\n");

    return 0;
}



// #define FILE_READ_BUF_SZ    1024


// extern void *my_dlopen(const char *file, int mode,
//         uint32_t file_crc32);


// int main(int argc, char **argv) {

//     // Check arguments.
//     if (argc != 3) {
//         printf("Wrong arguments numbers.\n");
//         exit(EXIT_FAILURE);
//     }

//     // argv[1] - path to lib
//     // argv[2] - its checksum
//     printf("Before my_dlopen().\n");
//     void *dlptr = my_dlopen(argv[1], RTLD_LAZY, atoi(argv[2]));
//     printf("After my_dlopen().\n");

//     if (dlptr == NULL) {
//         printf("Couldn't open given library OR check FAIL.\n");
//         exit(EXIT_FAILURE);
//     } else {
//         printf("File check PASS.\n");
//     }

//     return 0;
// }

// void *my_dlopen(const char *file, int mode,
//         uint32_t file_crc32) {

//     FILE *fd = fopen(file, "r");
//     if (fd == NULL) {
//         printf("Couldn't read file : %s\n", file);
//         return NULL;
//     }

//     unsigned char rb[FILE_READ_BUF_SZ] = { 0 };
//     // Nullify variables.
//     memset(rb, 0x00, FILE_READ_BUF_SZ);
//     // Number of Read Bytes.
//     size_t nrb = fread(rb, sizeof(rb[0]),
//             FILE_READ_BUF_SZ, fd);
//     fclose(fd);

//     // Check library checksum.
//     if (file_crc32 != crc32(rb, nrb)) {
//         printf("File checksum check didn't pass : %s\n", file);
//         return NULL;
//     }

//     // Open .so file.
//     void *result = dlopen(file, mode);
//     if (NULL == result) {
//         printf("ERROR dlopen: %s\n", dlerror());
//     }

//     return result;
// }