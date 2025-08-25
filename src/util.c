#include "util.h"
#include <stdio.h>

int util_readFile(const char* filePath, int maxLineLength, callback_ptr cb){
    FILE* fptr;
    char buffer[maxLineLength];
    
    fptr = fopen(filePath, "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(buffer, maxLineLength, fptr) != NULL){
        cb(buffer);
    }

    if (feof(fptr)){
        fprintf(stdout, "EOF\n");
    }
    else {
        perror("Error reading file");
    }

    if (fclose(fptr) != 0){
        perror("Error closing file");
        return -1;
    }
    
    return 0;
}

void util_printBuffer(const char* string){
    fprintf(stdout, "%s\n", string);
}
