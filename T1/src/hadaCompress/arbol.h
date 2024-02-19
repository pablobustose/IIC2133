#pragma once
#include "../imagelib/imagelib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct nodo_struct {
    int x;
    int y;
    int ancho;
    int alto;
    struct nodo_struct* hijos[4];
    double L_promedio;
    double a_promedio;
    double b_promedio;
    double L_desvesta;
    double a_desvesta;
    double b_desvesta;
    double gamma;
    double suma2_L;
    double suma2_a;
    double suma2_b;
} Nodo;

Nodo* crear_nodo(int x, int y, int ancho, int alto);

void crear_arbol(Nodo* raiz, Image* imagen);

void llenar_promedios(Nodo* raiz);

double calcular_promedio(double valor1, double valor2, double valor3, double valor4);

void filtro_alpha(Nodo* raiz, double alpha, Image* imagen);

void calcular_suma2(Nodo* nodo);

void llenar_desvestas(Nodo* raiz);

int cantidad_hojas(Nodo* raiz, int alpha);

int minimo_alpha(Nodo* raiz, int alpha, int inicio, int fin, int cantidad_hojas);

void free_arbol(Nodo* raiz);

