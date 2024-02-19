#include "graph.h"



Node* create_node(int id) {
    Node* node = calloc(1, sizeof(Node));
    node->id = id;
    node->neighbors = calloc(MAX_NEIGHBORS, sizeof(Node*));
    node->neighbors_count = 0;
    node->visited = 0;
    return node;
}


void add_neighbor(Node* node1, Node* node2) {
    node1->neighbors[node1->neighbors_count] = node2;
    node1->neighbors_count++;

    node2->neighbors[node2->neighbors_count] = node1;
    node2->neighbors_count++;
}

void CheckGraph(Node** nodes, int largo, int* visitados, FILE* output_file) {
    int contador = 0;
    for (int i = 0; i < largo; i++) {
        visitados[i] = DfsSearch(nodes, largo, i);
        if (visitados[i] > 1) {
            contador++;
        }
        FixNodes(nodes, largo);
    }
    fprintf(output_file, "%d\n", contador);
    for (int i = 0; i < largo; i++) {
        if (visitados[i] > 1) {
            fprintf(output_file, "%d %d\n", i, visitados[i]);
        }
    }
}

void FixNodes(Node** nodes, int largo) {
    for (int i = 0; i < largo; i++) {
        nodes[i]->visited = 0;
    }
}

int DfsSearch(Node** nodes, int largo, int id) {
    int contador = 0;
    for (int i = 0; i < largo; i++) {
        if (nodes[i]->visited == 0 && nodes[i]->id != id) {
            contador++;
            dfs(nodes[i], id);
        }
    }
    return contador;
}

void dfs(Node* node, int id) {
    node->visited = 1;
    for (int i = 0; i < node->neighbors_count; i++) {
        if (node->neighbors[i]->visited == 0 && node->neighbors[i]->id != id) {
            dfs(node->neighbors[i], id);
        }
    }
}


void free_node(Node* node) {
    free(node->neighbors);
    free(node);
}


