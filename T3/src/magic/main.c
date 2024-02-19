#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

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
    int largo;
    fscanf(input_file, "%d", &largo);

    Node** nodos = calloc(largo, sizeof(Node*)); //array con nodos
    int* visitados = calloc(largo, sizeof(int)); //array con visitados


    for (int i = 0; i < largo; i++) {
        nodos[i] = create_node(i);
    }

    int aristas;
    fscanf(input_file, "%d", &aristas);

    for (int i = 0; i < aristas; i++) {
        int nodo1, nodo2;
        fscanf(input_file, "%d %d", &nodo1, &nodo2);
        add_neighbor(nodos[nodo1 - 1], nodos[nodo2 - 1]);
    }

    CheckGraph(nodos, largo, visitados, output_file);

       
    for (int i = 0; i < largo; i++) {
        free_node(nodos[i]);
    }
    free(nodos);
    fclose(input_file);
    fclose(output_file);

    return 0;
}
