/*
 * Utility gets number of a file path, calculate CRC32
 * checksum for each of it, then write it to special file.
 * 
 * Using : ccrc32 <file1> <file2> ...
 * 
 */
#include "crc32.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>


#define CRC32_FILENAME "checksum_"__TIME__""__DATE__".txt"


inline bool is_file_exists (char *filename) {
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

    for (int i = 1; i < argc; ++i) {
    }
}