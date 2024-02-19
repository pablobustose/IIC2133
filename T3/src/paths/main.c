#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

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


    int cantidad_nodos; //600
    fscanf(input_file, "%d", &cantidad_nodos); 
    Node** nodos = calloc(cantidad_nodos, sizeof(Node*)); //array con 600 nodos
    for (int i = 0; i < cantidad_nodos; i++) {
        int x, y;
        fscanf(input_file, "%d %d", &x, &y);
        nodos[i] = node_create(x, y, i);
    }

    //cantidad de conexiones en base a combinatoria sobre 2
    int cantidad_conexiones = cantidad_nodos * (cantidad_nodos - 1) / 2; //179700
    Heap* conexiones = heap_create(cantidad_conexiones);

    for (int i = 0; i < cantidad_nodos; i++) {
        for (int j = i + 1; j < cantidad_nodos; j++) {
            Conection* conect = conection_create(nodos[i], nodos[j]);
            heap_insert(conexiones, conect);
        } 
    }
    int* padres = calloc(cantidad_nodos, sizeof(int));
    Conection** final_conections = calloc(cantidad_conexiones, sizeof(Conection*));
    for (int i = 0; i < cantidad_nodos; i++) {
        padres[i] = i;
    }
    int contador = 0;
    int sum = 0;
    //desde aca puede estar malo, cantidad conexiones es 179700 y me lanza error despues
    for (int i = 0; i < cantidad_conexiones; i++) {
        Conection* conection = heap_pop_min(conexiones);
        //fprintf(output_file, "nodo %d cuyo padre es %d, se compara antes con nodo %d cujo padre es %d\n", conection->node1->id, padres[conection->node1->id], conection->node2->id, padres[conection->node2->id]);
        if (padres[conection->node1->id] != padres[conection->node2->id]) {
            final_conections[contador] = conection;
            contador++;
            sum += conection->distance;
            if (padres[conection->node1->id] > padres[conection->node2->id]) {
                union_kruskal(padres, conection->node1, conection->node2, cantidad_nodos);
            } else {
                union_kruskal(padres, conection->node2, conection->node1, cantidad_nodos);
            }
            //fprintf(output_file, "nodo %d cuyo padre es %d, se une con nodo %d cujo padre es %d\n", conection->node1->id, padres[conection->node1->id], conection->node2->id, padres[conection->node2->id]);
            //fprintf(output_file, "%d %d %d %d %d %d\n", padres[0], padres[1], padres[2], padres[3], padres[4], padres[5]);
        } else {
            free(conection);
        }
    }

    fprintf(output_file, "%d\n", sum);
    for (int i = 0; i < contador; i++) {
        fprintf(output_file, "%d %d %d %d\n", final_conections[i]->node1->x, final_conections[i]->node1->y, final_conections[i]->node2->x, final_conections[i]->node2->y);
    }

    for (int i = 0; i < cantidad_nodos; i++) {
        free(nodos[i]);
    }
    free(nodos);
    free(padres);
    free_heap(conexiones);
    for (int i = 0; i < contador; i++) {
        free(final_conections[i]);
    }
    free(final_conections);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
