#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }

  return true;
}
int main(int argc, char** argv) {
    check_arguments(argc, argv);

    /* NO MODIFICAR */
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");
    /* NO MODIFICAR */

    int node_count;
    int query_count;

    /* leemos Cada nodo */
    fscanf(input_file, "%d", &node_count);
    int value;
    Nodo* raiz;
    Nodo* nodo;
    fscanf(input_file, "%d", &value);
    raiz = crear_nodo(value);

    int k;
    for(int i=1; i<node_count; i++){
        fscanf(input_file, "%d", &k);
        nodo = crear_nodo(k);
        insertar_nodo(raiz, nodo);
    }
    //imprimir_arbol(raiz); //borrar mas adelante

    fscanf(input_file, "%d", &query_count);
    /* leemos las consultas */
    char command[32];
    for(int i=0; i<query_count; i++){
        fscanf(input_file, "%s %d", command, &value);
        if (string_equals(command, "PATH")) {
          buscar_path(raiz, value, output_file);
        }
        else if (string_equals(command, "DEEP")) {
          deep_value(raiz, value, output_file);
        }
        else if (string_equals(command, "ORDER")) {
          if (raiz->invertido) {
            ordenar(raiz, output_file, true);
          }
          else {
            ordenar(raiz, output_file, false);
          }
          fprintf(output_file, "\n");
        }
        else if (string_equals(command, "DEEP-ORDER")) {
          imprimir_niveles(raiz, output_file, raiz->invertido);
          fprintf(output_file, "\n");
        }
        else if (string_equals(command, "INVERT")) {
          invertir(raiz);
          if (raiz->invertido) {
            raiz->invertido = false;
          }
          else {
            raiz->invertido = true;
          }
          //llamar a deep order
          imprimir_niveles(raiz, output_file, false);
          fprintf(output_file, "\n");

        }
        else {
          printf("Comando no reconocido: %s\n", command);
        }
    }

    //liberar memoria
    liberar_memoria(raiz);


    fclose(input_file);
    fclose(output_file);
    return 0;
}

