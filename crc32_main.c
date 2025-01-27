/*
 * Utility gets number of a file path, calculate CRC32
 * checksum for each of it, then write it to special file.
 * 
 * Using : ccrc <file1> <file2> ...
 * 
 */
#include "crc32.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>


#define CRC32_FILENAME      "checksum_"__TIME__""__DATE__".txt"
#define FILE_READ_BUF_SZ    1024


bool is_file_exists (char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}


int main(int argc, char **argv)  {
    
    // Checking arguments number.
    if (argc < 2) {
        printf("Too small arguments.\n");
        exit(EXIT_FAILURE);
    }
    
    // Checking files paths.
    bool is_paths_correct = true;
    for (int i = 1; i < argc; ++i) {
        if (false == is_file_exists(argv[i])) {
            printf("Wrong path : %s\n", argv[i]);
            is_paths_correct = false;
        }
    }
    if (false == is_paths_correct) {
        exit(EXIT_FAILURE);
    }

    FILE *fd = NULL; // File Descriptor.
    unsigned char rb[FILE_READ_BUF_SZ] = { 0 }; // Read Buffer.
    uint32_t fcs = 0U; // File Control Sum.
    for (int i = 1; i < argc; ++i) {
        fd = fopen(argv[i], "r");
        if (fd == NULL) {
            printf("Couldn't read file : %s\n", argv[i]);
            continue;
        }

        // Nullify variables.
        memset(rb, 0x00, FILE_READ_BUF_SZ);
        fcs = 0U;
        // Number of Read Bytes.
        size_t nrb = fread(rb, sizeof(rb[0]),
                FILE_READ_BUF_SZ, fd);
        fcs = crc32(rb, nrb);

        printf("-----\nFile : %s\nCRC32 : %u\n",
                argv[i], fcs);
        fclose(fd);
    }

    printf("-----\n");
}