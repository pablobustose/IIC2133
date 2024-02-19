#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tile.h"
#include "celda.h"


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
    int width;
    int height;
    fscanf(input_file, "%d", &width);
    fscanf(input_file, "%d", &height);

    //crear mapa
    Celda*** mapa = calloc(height, sizeof(Celda**));
    for (int k = 0; k < height; k++) {
        mapa[k] = calloc(width, sizeof(Celda*));
        for (int j = 0; j < width; j++) {
            mapa[k][j] = crear_celda(k, j, NULL); // Puedes inicializarlo con NULL o el valor apropiado
            mapa[k][j]->inicial = true;
        }
    }

    int sizeSet;
    fscanf(input_file, "%d", &sizeSet);
    char arriba;
    char abajo;
    char derecha;
    char izquierda;
    Tile* tile;
    Tile** tiles_disponibles = calloc(sizeSet, sizeof(Tile*)); //se declara array de punteros a tiles
    fgetc(input_file);

    //crear tiles disponibles
    for(int i=0; i<sizeSet; i++){
      fscanf(input_file, " %c %c %c %c", &arriba, &derecha, &abajo, &izquierda); 
      tile = crear_tile(arriba, derecha, abajo, izquierda, i); //tile es puntero a tipo Tile
      tiles_disponibles[i] = tile; //se insertan al array
    }

    //lenar mapa con tiles iniciales
    int n_tiles;
    int columna;
    int fila;
    int tile_index;
    fscanf(input_file, "%d", &n_tiles);
    for(int j=0; j<n_tiles; j++){
      fscanf(input_file, "%d %d %d", &columna, &fila, &tile_index);
      mapa[fila][columna]->tile = tiles_disponibles[tile_index]; //se insertan en el mapa
      //mapa[fila][columna]->visitado = true; //se marca como visitado
    }
    //mapa[fila][columna]->visitado = false;

    generar_mapa(mapa, tiles_disponibles, mapa[fila][columna]->tile, fila, columna, height, width, sizeSet, output_file);
    
    imprimir_mapa(mapa, height, width, output_file);




    liberar_mapa(mapa, height, width);
    liberar_tiles(tiles_disponibles, sizeSet);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
