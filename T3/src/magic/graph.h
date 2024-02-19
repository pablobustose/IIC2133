#pragma once

#include <stdlib.h>
#include <stdio.h>
#define MAX_NEIGHBORS 30

typedef struct node_t {
    int id;
    struct node_t **neighbors; // array de punteros a nodos
    int visited;
    int neighbors_count;
} Node;

Node *create_node(int id);

void add_neighbor(Node *node1, Node *node2);

int DfsSearch(Node **nodes, int largo, int id);

//int dfs(int id, Node **nodes, int largo);

void CheckGraph(Node **nodes, int largo, int* visitados, FILE *output_file);

void FixNodes(Node **nodes, int largo);

void dfs(Node *node, int id);

void free_node(Node *node);
