#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_struct {
    int value;
    struct nodo_struct* hijo_derecho; //puntero a nodo hijo derecho
    struct nodo_struct* hijo_izquierdo; //puntero a nodo hijo izquierdo
    struct nodo_struct* padre; //puntero a nodo padre
    bool invertido;
} Nodo;

Nodo* crear_nodo(int value);

void insertar_nodo(Nodo* raiz, Nodo* nodo);

void imprimir_arbol(Nodo* raiz);

void buscar_path(Nodo* raiz, int valor, FILE* output_file);

void deep_value(Nodo* raiz, int valor, FILE* output_file);

void ordenar(Nodo* raiz, FILE* output_file, bool invertido);

void invertir(Nodo* raiz);

int altura_arbol(Nodo* raiz);

void imprimir_niveles(Nodo* raiz, FILE* output_file, bool invertido);

void imprimir_nivel(Nodo* raiz, int nivel, FILE* output_file, bool invertido);

void liberar_memoria(Nodo* raiz);
