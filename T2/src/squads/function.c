#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"

int compareChars(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// ordenar una cadena alfabéticamente
void sortString(char* str) {
    size_t len = strlen(str);
    qsort(str, len, sizeof(char), compareChars);
}