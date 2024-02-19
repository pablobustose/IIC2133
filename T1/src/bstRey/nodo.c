#include "nodo.h"

Nodo* crear_nodo(int value) {
    Nodo* nodo = calloc(1, sizeof(Nodo));
    nodo->value = value;
    nodo->hijo_derecho = NULL;
    nodo->hijo_izquierdo = NULL;
    nodo->padre = NULL;
    nodo->invertido = false;
    return nodo;
}

void insertar_nodo(Nodo* raiz, Nodo* nodo) {
    Nodo* nodo_actual = raiz;
    bool fue_insertado = false;
    while (!fue_insertado) {
        if (nodo_actual->value > nodo->value) {
            if (nodo_actual->hijo_izquierdo != NULL) {
                nodo_actual = nodo_actual->hijo_izquierdo;
            }
            else {
                nodo_actual->hijo_izquierdo = nodo;
                nodo->padre = nodo_actual;
                fue_insertado = true;
            }
        } 
        else if (nodo_actual->value < nodo->value) {
            if (nodo_actual->hijo_derecho != NULL) {
                nodo_actual = nodo_actual->hijo_derecho;
            }
            else {
                nodo_actual->hijo_derecho = nodo;
                nodo->padre = nodo_actual;
                fue_insertado = true;
            }
        } 
    }
}
void imprimir_arbol(Nodo* raiz) {
    printf("%d ", raiz->value);
    if (raiz->hijo_izquierdo != NULL) {
        imprimir_arbol(raiz->hijo_izquierdo);
    }
    if (raiz->hijo_derecho != NULL) {
        imprimir_arbol(raiz->hijo_derecho);
    }
}

void buscar_path(Nodo* raiz, int valor, FILE* output_file) {
    //aplicar if invertido, ya que se va hacia el sentido que depende de si está invertido
    Nodo* nodo_actual = raiz;
    bool encontrado = false;
    while (!encontrado) {
        if (nodo_actual->value == valor) {
            fprintf(output_file, "%d \n", valor);
            encontrado = true;
        }
        else if (nodo_actual->value > valor) {
            if (raiz->invertido) {
                if (nodo_actual->hijo_derecho != NULL) {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    nodo_actual = nodo_actual->hijo_derecho;
                }
                else {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    fprintf(output_file, "X\n");
                    encontrado = true;
                }
            }
            else {
                if (nodo_actual->hijo_izquierdo != NULL) {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    nodo_actual = nodo_actual->hijo_izquierdo;
                }
                else {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    fprintf(output_file, "X\n");
                    encontrado = true;
                }
            }
        }
        else if (nodo_actual->value < valor) {
            if (raiz->invertido) {
                if (nodo_actual->hijo_izquierdo != NULL) {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    nodo_actual = nodo_actual->hijo_izquierdo;
                }
                else {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    fprintf(output_file, "X\n");
                    encontrado = true;
                }

            }
            else {
                if (nodo_actual->hijo_derecho != NULL) {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    nodo_actual = nodo_actual->hijo_derecho;
                }
                else {
                    fprintf(output_file, "%d ", nodo_actual->value);
                    fprintf(output_file, "X\n");
                    encontrado = true;
                }
            }
        } 
    }
}

void deep_value(Nodo* raiz, int valor, FILE* output_file) {
    Nodo* nodo_actual = raiz;
    bool encontrado = false;
    int contador = -1;
    while (!encontrado) {
        contador ++;
        if (nodo_actual->value == valor) {
            fprintf(output_file, "%d\n", contador);
            encontrado = true;
        }
        else if (nodo_actual->value > valor) {
            if (raiz->invertido) {
                if (nodo_actual->hijo_derecho != NULL) {
                    nodo_actual = nodo_actual->hijo_derecho;
                }
                else {
                    fprintf(output_file, "-1\n");
                    encontrado = true;
                }
            }
            else {
                if (nodo_actual->hijo_izquierdo != NULL) {
                    nodo_actual = nodo_actual->hijo_izquierdo;
                }
                else {
                    fprintf(output_file, "-1\n");
                    encontrado = true;
                }
            }
        }
        else if (nodo_actual->value < valor) {
            if (raiz->invertido) {
                if (nodo_actual->hijo_izquierdo != NULL) {
                    nodo_actual = nodo_actual->hijo_izquierdo;
                }
                else {
                    fprintf(output_file, "-1\n");
                    encontrado = true;
                }
            }
            else {
                if (nodo_actual->hijo_derecho != NULL) {
                    nodo_actual = nodo_actual->hijo_derecho;
                }
                else {
                    fprintf(output_file, "-1\n");
                    encontrado = true;
                }
            }
        } 
    }
}

void ordenar(Nodo* raiz, FILE* output_file, bool invertido) {  
    if (!invertido) {
        if (raiz->hijo_izquierdo != NULL) {
            ordenar(raiz->hijo_izquierdo, output_file, false);
        }
        fprintf(output_file, "%d ", raiz->value);
        if (raiz->hijo_derecho != NULL) {
            ordenar(raiz->hijo_derecho, output_file, false);
        }
    }
    else {
        if (raiz->hijo_derecho != NULL) {
            ordenar(raiz->hijo_derecho, output_file, true);
        }
        fprintf(output_file, "%d ", raiz->value);
        if (raiz->hijo_izquierdo != NULL) {
            ordenar(raiz->hijo_izquierdo, output_file, true);
        }
    }
}

void invertir(Nodo* raiz) {
    Nodo* hijo_izquierdo = raiz->hijo_izquierdo;
    Nodo* hijo_derecho = raiz->hijo_derecho;
    raiz->hijo_izquierdo = hijo_derecho;
    raiz->hijo_derecho = hijo_izquierdo;
    if (hijo_izquierdo != NULL) {
        invertir(hijo_izquierdo);
    }
    if (hijo_derecho != NULL) {
        invertir(hijo_derecho);
    }
}

void liberar_memoria(Nodo* raiz) {
    Nodo* hijo_izquierdo = raiz->hijo_izquierdo;
    Nodo* hijo_derecho = raiz->hijo_derecho;
    free(raiz);
    if (hijo_izquierdo != NULL) {
        liberar_memoria(hijo_izquierdo);
    }
    if (hijo_derecho != NULL) {
        liberar_memoria(hijo_derecho);
    } 
}

int altura_arbol(Nodo* raiz) {
    if (raiz == NULL) {
        return 0;
    } else {
        int alturaIzquierda = altura_arbol(raiz->hijo_izquierdo);
        int alturaDerecha = altura_arbol(raiz->hijo_derecho);

        if (alturaIzquierda > alturaDerecha) {
            return alturaIzquierda + 1;
        } else {
            return alturaDerecha + 1;
        }
    }
}

void imprimir_niveles(Nodo* raiz, FILE* output_file, bool invertido) {
    int altura = altura_arbol(raiz);
    for (int nivel = 1; nivel <= altura; nivel++) {
        imprimir_nivel(raiz, nivel, output_file, invertido);
    }
}

void imprimir_nivel(Nodo* raiz, int nivel, FILE* output_file, bool invertido) {
    if (raiz == NULL) {
        return;
    }
    if (nivel == 1) {
        fprintf(output_file, "%d ", raiz->value);
    } else if (nivel > 1) {
        if (invertido) {
            imprimir_nivel(raiz->hijo_derecho, nivel - 1, output_file, invertido);
            imprimir_nivel(raiz->hijo_izquierdo, nivel - 1, output_file, invertido);
        }
        else {
            imprimir_nivel(raiz->hijo_izquierdo, nivel - 1, output_file, invertido);
            imprimir_nivel(raiz->hijo_derecho, nivel - 1, output_file, invertido);
        }
    }
}