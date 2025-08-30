#include "util.h"
#include <stdio.h>

int util_readFile(const char* filePath, int maxLineLength, TokenList* list, callback_ptr cb){
    FILE* fptr;
    char buffer[maxLineLength];
    
    fptr = fopen(filePath, "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return UTIL_FAILURE;
    }

    while (fgets(buffer, maxLineLength, fptr) != NULL){
        cb(buffer, list);
    }

    if (feof(fptr)){
        fprintf(stdout, "EOF\n");
    }
    else {
        perror("Error reading file");
    }

    if (fclose(fptr) != 0){
        perror("Error closing file");
        return UTIL_FAILURE;
    }
    
    return 0;
}

void util_printBuffer(const char* string){
    fprintf(stdout, "%s\n", string);
}

int util_isNum(char t){
    if ((int)t >= 48 && (int)t <= 57){
        return UTIL_TRUE;
    }
    return UTIL_FALSE;
}

int util_isAlpha(char t){
    if ((int)t >= 97 && (int)t <= 122){
        return UTIL_TRUE;
    }
    else if ((int)t >= 65 && (int)t <= 90){
        return UTIL_TRUE;
    }
    else if (t == '-' || t == '.'){ // For now, we'll allow a dash and a period as a regular letter
        return UTIL_TRUE;
    }
    return UTIL_FALSE;
}

int util_isAlphaNum(char t){
    return util_isNum(t) || util_isAlpha(t);
}
