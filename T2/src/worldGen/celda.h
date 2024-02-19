#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tile.h"

typedef struct celda_struct {
    Tile* tile;
    bool visitado;
    bool inicial;
    int fila;
    int columna;
} Celda;

Celda* crear_celda(int fila, int columna, Tile* tile);

bool posicion_valida(int fila, int columna, Celda*** mapa, int height, int width, Tile* tile);

bool tile_posicion_final(Celda*** mapa, int fila, int columna, int height, int width, Tile* tile, FILE* output_file);

bool generar_mapa(Celda*** mapa, Tile** tiles_disponibles, Tile* tile, int fila, int columna, int height, int width, int sizeSet, FILE* output_file);

bool revisar_mapa(Celda*** mapa, int height, int width);

void imprimir_mapa(Celda*** mapa, int height, int width, FILE* output_file);

void liberar_mapa(Celda*** mapa, int height, int width);