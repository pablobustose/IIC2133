#include "pueblo.h"

Pueblo* create_Pueblo_item(unsigned long ganancia) {
    Pueblo* item = calloc(1, sizeof(Pueblo));
    item->ganancia = ganancia;
    return item;
}

unsigned long max(unsigned long a, unsigned long b) {
  return a > b ? a : b;
}

void free_pueblos(Pueblo** pueblos, int largo) {
    for (int i = 0; i < largo; i++) {
        free(pueblos[i]);
    }
    free(pueblos);
}

unsigned long dynamic_programming_iterative(Pueblo** pueblos, int largo) {
    unsigned long* M = calloc(largo + 1, sizeof(unsigned long));
    for (int i = largo - 1; i >= 0; --i) {
        if (i >= largo - 3) {
            //últimos 3 pueblos
            M[i] = max(M[i + 1], pueblos[i]->ganancia);
        } else {
            M[i] = max(M[i + 1], M[i + 3] + pueblos[i]->ganancia);
        }
    }
    unsigned long resultado = M[0];
    free(M);
    return resultado;
}
