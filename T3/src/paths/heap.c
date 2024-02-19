#include "heap.h"

Heap *heap_create(int size) {
    Heap *heap = calloc(1, sizeof(Heap));
    heap->size = size; //179700
    heap->capacity = 0;
    heap->conections = calloc(size, sizeof(Conection*)); //array con 179700 conexiones
    return heap;
}

Conection *conection_create(Node *node1, Node *node2) {
    Conection *conection = calloc(1, sizeof(Conection));
    conection->node1 = node1;
    conection->node2 = node2;
    conection->distance = get_distance(node1, node2);
    return conection;
}

Node *node_create(int x, int y, int id) {
    Node *node = calloc(1, sizeof(Node));
    node->x = x;
    node->y = y;
    node->id = id;
    return node;
}

Conection *heap_pop_min(Heap *heap) {
    Conection* min = heap->conections[0];
    heap->conections[0] = heap->conections[heap->capacity - 1];
    //no se si esta bien este 0
    //heap->conections[heap->capacity - 1] = 0;
    heap->capacity--;
    heapify_down(heap, 0);
    return min;
}

void heapify_up(Heap *heap, int index) {
    int parent_index = (index - 1) / 2;             //si el padre es mayor que el hijo, intercambiar
    if (index > 0 && heap->conections[parent_index]->distance > heap->conections[index]->distance) {
        Conection* temp = heap->conections[index];
        heap->conections[index] = heap->conections[parent_index];
        heap->conections[parent_index] = temp;
        heapify_up(heap, parent_index);
    }
}

void heapify_down(Heap *heap, int index) {
    int left_index = index * 2 + 1;
    int right_index = index * 2 + 2;
    int min_index = index;                            //si el hijo es menor que el padre, intercambiar
    if (left_index < heap->capacity && heap->conections[left_index]->distance < heap->conections[min_index]->distance) {
        min_index = left_index;
    }                                                  //si el hijo es menor que el padre, intercambiar
    if (right_index < heap->capacity && heap->conections[right_index]->distance < heap->conections[min_index]->distance) {
        min_index = right_index;
    } //si se dio que el hijo es menor, intercambiar
    if (min_index != index) {
        Conection* temp = heap->conections[index];
        heap->conections[index] = heap->conections[min_index];
        heap->conections[min_index] = temp;
        heapify_down(heap, min_index);
    }
}

void heap_insert(Heap *heap, Conection *conection) {
    heap->conections[heap->capacity] = conection;
    heapify_up(heap, heap->capacity);
    heap->capacity++;
}

int get_distance(Node* node1, Node* node2) {
    return abs(node1->x - node2->x) + abs(node1->y - node2->y);
}

void free_heap(Heap *heap) {
    for (int i = 0; i < heap->capacity; i++) {
        free(heap->conections[i]);
    }
    free(heap->conections);
    free(heap);
}

void union_kruskal(int* padres, Node* node1, Node* node2, int largo) {
    //el nodo 2 pasa a ser padre del nodo 1
    int viejo = padres[node1->id];
    int nuevo = padres[node2->id];
    padres[node1->id] = padres[node2->id];
    for (int i = 0; i < largo; i++) {
        if (padres[i] == viejo) {
            padres[i] = nuevo;
        }
    }

}

