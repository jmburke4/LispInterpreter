#include "util.h"
#include <stdio.h>

void util_printBuffer(const char* string){
    fprintf(stdout, "%s\n", string);
}

int util_isNum(char t){
    if (((int)t >= 48 && (int)t <= 57) || t == '.'){
        // Include period for floating point numbers
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
    return UTIL_FALSE;
}

int util_isAlphaNum(char t){
    return util_isNum(t) || util_isAlpha(t);
}
