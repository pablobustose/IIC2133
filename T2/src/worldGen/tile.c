#include "tile.h"



Tile* crear_tile(char arriba, char derecha, char abajo, char izquierda, int index) {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->arriba = arriba;
    tile->derecha = derecha;
    tile->abajo = abajo;
    tile->izquierda = izquierda;
    tile->index = index;
    tile->visitado = false;
    return tile;
}


void liberar_tiles(Tile** tiles_disponibles, int sizeSet) {
    for (int i = 0; i < sizeSet; i++) {
        free(tiles_disponibles[i]);
    }
    free(tiles_disponibles);
}

