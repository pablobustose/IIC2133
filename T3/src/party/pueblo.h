#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct pueblo_t {
    unsigned long ganancia;
} Pueblo;

Pueblo* create_Pueblo_item(unsigned long ganancia);
unsigned long max(unsigned long a, unsigned long b);
void free_pueblos(Pueblo** pueblos, int largo);
unsigned long dynamic_programming_iterative(Pueblo** pueblos, int largo);
