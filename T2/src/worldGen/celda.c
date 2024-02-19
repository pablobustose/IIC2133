#include "celda.h"
Celda* crear_celda(int fila, int columna, Tile* tile) {
    Celda* celda = calloc(1, sizeof(Celda));
    celda->fila = fila;
    celda->columna = columna;
    celda->tile = tile;
    celda->visitado = false;
    celda->inicial = false;
    return celda;
}

bool posicion_valida(int fila, int columna, Celda*** mapa, int height, int width, Tile* tile) {
    //si la posicion esta ocupada y visitada
    if (mapa[fila][columna]->tile != NULL) {
        if (mapa[fila][columna]->visitado == true || mapa[fila][columna]->inicial == true) {
            return false;
        }
    }

    //coincide arriba
    if (fila > 0) {
        if (mapa[fila - 1][columna]->tile != NULL) {
            if (tile->arriba != mapa[fila - 1][columna]->tile->abajo) {
                return false;
            }
        }
    }
    //coincide abajo
    if (fila < height - 1) {
        if (mapa[fila + 1][columna]->tile != NULL) {
            if (tile->abajo != mapa[fila + 1][columna]->tile->arriba) {
                return false;
            }
        }
    }
    //coincide derecha
    if (columna < width - 1) {
        if (mapa[fila][columna + 1]->tile != NULL) {
            if (tile->derecha != mapa[fila][columna + 1]->tile->izquierda) {
                return false;
            }
        }
    }
    //coincide izquierda
    if (columna > 0) {
        if (mapa[fila][columna - 1]->tile != NULL) {
            if (tile->izquierda != mapa[fila][columna - 1]->tile->derecha) {
                return false;
            }
        }
    }
    return true;
}

bool tile_posicion_final(Celda*** mapa, int fila, int columna, int height, int width, Tile* tile, FILE* output_file) {
    //coincide arriba
    if (fila > 0) {
        if (mapa[fila - 1][columna]->tile == NULL) {
            //fprintf(output_file, "No hay tile arriba\n"); 
            return false;
        }
        if (mapa[fila][columna]->tile->arriba != mapa[fila - 1][columna]->tile->abajo) {
            //fprintf(output_file, "No coincide arriba\n");
            return false;
        }
    }
    //coincide abajo
    if (fila < height - 1) {
        if (mapa[fila + 1][columna]->tile == NULL) {
            //fprintf(output_file, "No hay tile abajo\n");
            return false;
        }
        if (mapa[fila][columna]->tile->abajo != mapa[fila + 1][columna]->tile->arriba) {
            //fprintf(output_file, "No coincide abajo\n");
            return false;
        }
    }
    //coincide derecha
    if (columna < width - 1) {
        if (mapa[fila][columna + 1]->tile == NULL) {
            //fprintf(output_file, "No hay tile derecha\n");
            return false;
        }
        if (mapa[fila][columna]->tile->derecha != mapa[fila][columna + 1]->tile->izquierda) {
            //fprintf(output_file, "No coincide derecha\n");
            return false;
        }
    }
    //coincide izquierda
    if (columna > 0) {
        if (mapa[fila][columna - 1]->tile == NULL) {
            //fprintf(output_file, "No hay tile izquierda\n");
            return false;
        }
        if (mapa[fila][columna]->tile->izquierda != mapa[fila][columna - 1]->tile->derecha) {
            //fprintf(output_file, "No coincide izquierda\n");
            //fprintf(output_file, "Tile izquierda %d, tile actual %d\n", mapa[fila][columna - 1]->tile->index, mapa[fila][columna]->tile->index);
            return false;
        }
    }
    return true;
} 

//recibe un tile, y revisa si es posible insertarlo en la posicion fila, columna del mapa
bool generar_mapa(Celda*** mapa, Tile** tiles_disponibles, Tile* tile, int fila, int columna, int height, int width, int sizeSet, FILE* output_file) {
    //imprimir_mapa(mapa, height, width, output_file);
    //fprintf(output_file,"Estoy en fila %d, columna %d y analizo %d \n", fila, columna, tile->index);
    if (revisar_mapa(mapa, height, width) == true) {
        return true;
    }
    if (mapa[fila][columna]->visitado == true) {
        //fprintf(output_file, "Celda visitado\n");
        return false;
    }
    mapa[fila][columna]->visitado = true;
    for (int i = 0; i < sizeSet; i++) {
        //verifica el de la derecha
        if (columna + 1 < width) {
            //fprintf(output_file, "Buscanco derecha desde fila %d, columna %d y probando indice %d\n", fila, columna, tiles_disponibles[i]->index);
            if (posicion_valida(fila , columna + 1, mapa, height, width, tiles_disponibles[i]) == true) {
                mapa[fila][columna + 1]->tile = tiles_disponibles[i];
                //imprimir_mapa(mapa, height, width);
                tile = tiles_disponibles[i];
                //fprintf(output_file, "Me muevo a fila %d, columna %d y agregue indice %d \n", fila, columna + 1, tile->index);
                if (generar_mapa(mapa, tiles_disponibles, tile, fila, columna + 1, height, width, sizeSet, output_file) == true) {
                    return true;
                }
                //fprintf(output_file, "Se desvisita fila %d, columna %d y indice %d \n", fila, columna, tile->index);
                mapa[fila][columna]->visitado = false;
                //mapa[fila][columna]->tile = NULL;
            }
        }
    }
    for (int i = 0; i < sizeSet; i++) {
        //verifica el de la izquierda
        if (columna - 1 >= 0) {
            //fprintf(output_file, "Buscanco izquierda desde fila %d, columna %d y probando indice %d\n", fila, columna, tiles_disponibles[i]->index);
            if (posicion_valida(fila , columna - 1, mapa, height, width, tiles_disponibles[i]) == true) {
                mapa[fila][columna - 1]->tile = tiles_disponibles[i];
                //imprimir_mapa(mapa, height, width);
                tile = tiles_disponibles[i];
                //fprintf(output_file, "Me muevo a fila %d, columna %d y agregue indice %d \n", fila, columna - 1, tile->index);
                if (generar_mapa(mapa, tiles_disponibles, tile, fila, columna - 1, height, width, sizeSet, output_file) == true) {
                    return true;
                }
                //fprintf(output_file, "Se desvisita fila %d, columna %d y indice %d \n", fila, columna, tile->index);
                mapa[fila][columna]->visitado = false;
                //mapa[fila][columna]->tile = NULL;

            }
        }
    }
    for (int i = 0; i < sizeSet; i++) {
        //verifica el de arriba
        if (fila - 1 >= 0) {
            //fprintf(output_file, "Buscanco arriba desde fila %d, columna %d y probando indice %d\n", fila, columna, tiles_disponibles[i]->index);
            if (posicion_valida(fila - 1 , columna, mapa, height, width, tiles_disponibles[i]) == true) {
                mapa[fila - 1][columna]->tile = tiles_disponibles[i];
                //imprimir_mapa(mapa, height, width);
                tile = tiles_disponibles[i];
                //fprintf(output_file, "Me muevo a fila %d, columna %d y agregue indice %d \n", fila - 1, columna, tile->index);
                if (generar_mapa(mapa, tiles_disponibles, tile, fila - 1, columna, height, width, sizeSet, output_file) == true) {
                    return true;
                }
                //fprintf(output_file, "Se desvisita fila %d, columna %d y indice %d \n", fila, columna, tile->index);
                mapa[fila][columna]->visitado = false;
                //mapa[fila][columna]->tile = NULL;
            }
        }
    }
    for (int i = 0; i < sizeSet; i++) {
        //verifica el de abajo
        if (fila + 1 < height) {
            //fprintf(output_file, "Buscanco abajo desde fila %d, columna %d y probando indice %d\n", fila, columna, tiles_disponibles[i]->index);
            if (posicion_valida(fila + 1 , columna, mapa, height, width, tiles_disponibles[i]) == true) {
                mapa[fila + 1][columna]->tile = tiles_disponibles[i];
                //imprimir_mapa(mapa, height, width);
                tile = tiles_disponibles[i];
                //fprintf(output_file, "Me muevo a fila %d, columna %d y agregue indice %d \n", fila + 1, columna, tile->index);
                if (generar_mapa(mapa, tiles_disponibles, tile, fila + 1, columna, height, width, sizeSet, output_file) == true) {
                    return true;
                }
                //fprintf(output_file, "Se desvisita fila %d, columna %d y indice %d \n", fila, columna, tile->index);
                mapa[fila][columna]->visitado = false;
                //mapa[fila][columna]->tile = NULL;

            }
        }
    }


    //fprintf(output_file, "No se puede insertar en fila %d, columna %d \n", fila, columna);
    //si el borde no está todo lleno, se borra el tile, porque si está todo lleno es que se llena al loop del caracol
    if (tile_posicion_final(mapa, fila, columna, height, width, tile, output_file) == false) {
        //fprintf(output_file, "Se elimina fila %d, columna %d y indice %d \n", fila, columna, tile->index);
        mapa[fila][columna]->tile = NULL;
        //mapa[fila][columna]->visitado = false;
    }
    mapa[fila][columna]->visitado = false;
    return false;
}

bool revisar_mapa(Celda*** mapa, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            if (mapa[i][k]->visitado == false) {
                return false;
            }
        }
    }
    //imprimirlo
    return true;
}

void imprimir_mapa(Celda*** mapa, int height, int width, FILE* output_file) {
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            if (mapa[i][k]->tile != NULL) {
                fprintf(output_file ,"%d ", mapa[i][k]->tile->index);
            } else {
                fprintf(output_file, "X ");
            }
        }
        fprintf(output_file, "\n");
    }
}


void liberar_mapa(Celda*** mapa, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            free(mapa[i][k]);
        }
        free(mapa[i]);
    }
    free(mapa);
    printf("Mapa liberado\n");
}