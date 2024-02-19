#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pueblo.h"


bool check_arguments(int argc, char **argv) {
    if (argc != 3) {
        printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
        printf("Donde:\n");
        printf("\tINPUT es la ruta del archivo de input\n");
        printf("\tOUTPUT es la ruta del archivo de output\n");
      
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    if (!check_arguments(argc, argv)) return 1;

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    if (input_file == NULL || output_file == NULL) {
        printf("Error al abrir los archivos\n");
        perror("Error al abrir el archivo");
        return 1;
    }

    int largo;
    if (fscanf(input_file, "%d", &largo) != 1) {
        fprintf(stderr, "Error al leer el número de pueblos\n");
        return 1;
    }
    //se define dynamic table para tener registro de valores
    unsigned long* M = calloc(largo, sizeof(unsigned long));
    // se almecenan los pueblos en el arreglo
    Pueblo** pueblos = calloc(largo, sizeof(Pueblo*));

    for (int i = 0; i < largo; i++) {
        unsigned long ganancia;
        fscanf(input_file, "%ld", &ganancia);
        pueblos[i] = create_Pueblo_item(ganancia);
    }
    // se llena la tabla y retorna máximo
    unsigned long maximo = dynamic_programming_iterative(pueblos, largo);
    // se imprime el valor maximo
    fprintf(output_file, "%ld\n", maximo);

    //se libera memoria
    free(M);
    free_pueblos(pueblos, largo);
    fclose(input_file);
    fclose(output_file);

    return 0;
}
