#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t {
    int x;
    int y;
    int id;
    int distance;
} Node;

typedef struct conections_t {
    Node *node1;
    Node *node2;
    int distance;
} Conection;

typedef struct heap_t {
    Conection **conections;
    int size;
    int capacity;
} Heap;

Heap *heap_create(int capacity);

Conection *conection_create(Node *node1, Node *node2);

Node *node_create(int x, int y, int id);

void heap_insert(Heap *heap, Conection *conection);

Conection *heap_pop_min(Heap *heap);

void heapify_up(Heap *heap, int index);

void heapify_down(Heap *heap, int index);

int get_distance(Node* node1, Node* node2);

void free_heap(Heap *heap);

void union_kruskal(int* padres, Node* nodo1, Node* nodo2, int largo);
