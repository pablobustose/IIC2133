#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"
#include "function.h"

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

    //tabla con 20 elementos
    HashItem** tabla = calloc(20, sizeof(HashItem*));
    char input[255] = "";
    int largo;

    while (!string_equals(input, "q")) {
      fscanf(input_file, "%s", input);
      if (string_equals(input, "+")) {
          fscanf(input_file, "%d", &largo);
          char escuadron[largo][2];
          for (int i = 0; i < largo; i++) {
              fscanf(input_file, "%s", escuadron[i]);
          }
          char texto[256] = "";
          for (int i = 0; i < largo; i++) {
              strcat(texto, &escuadron[i][0]);
          }
          sortString(texto);
          insert_or_update(tabla, largo, texto, 20);
      }
      else if (string_equals(input, "?")) {
          fscanf(input_file, "%d", &largo);
          char escuadron[largo][2];
          for (int i = 0; i < largo; i++) {
              fscanf(input_file, "%s", escuadron[i]);
          }
          char texto[256] = "";
          for (int i = 0; i < largo; i++) {
              strcat(texto, &escuadron[i][0]);
          }
          sortString(texto);
          int veces = fetch_value(tabla, largo, texto, 20);
          fprintf(output_file, "%d\n", veces);
      };
    }
    free_hash_table(tabla, 20);
    fclose(input_file);
    fclose(output_file);
    return 0;
}

