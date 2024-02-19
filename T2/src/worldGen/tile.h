#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct tile_struct {
    char arriba;
    char derecha;
    char abajo;
    char izquierda; 
    bool visitado;
    int index;
} Tile;

Tile* crear_tile(char arriba, char derecha, char abajo, char izquierda, int index);

void liberar_tiles(Tile** tiles_disponibles, int sizeSet);
