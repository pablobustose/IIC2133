#include "arbol.h"


Nodo* crear_nodo(int x, int y, int ancho, int alto) {
    Nodo* nodo = calloc(1, sizeof(Nodo));
    nodo -> x = x;
    nodo -> y = y;
    nodo -> ancho = ancho;
    nodo -> alto = alto;
    nodo -> L_promedio = 0;
    nodo -> a_promedio = 0;
    nodo -> b_promedio = 0;
    nodo -> L_desvesta = 0;
    nodo -> a_desvesta = 0;
    nodo -> b_desvesta = 0;
    nodo -> gamma = 0;
    nodo -> hijos[0] = NULL;
    nodo -> hijos[1] = NULL;
    nodo -> hijos[2] = NULL;
    nodo -> hijos[3] = NULL;
    return nodo;
}

void crear_arbol(Nodo* raiz, Image* imagen) {
    if (raiz->ancho > 1 && raiz->alto > 1) {
        raiz->hijos[0] = crear_nodo(raiz->x, raiz->y, raiz->ancho/2, raiz->alto/2);
        crear_arbol(raiz->hijos[0], imagen);
        raiz->hijos[1] = crear_nodo(raiz->x + raiz->ancho/2, raiz->y, raiz->ancho/2, raiz->alto/2);
        crear_arbol(raiz->hijos[1], imagen);
        raiz->hijos[2] = crear_nodo(raiz->x, raiz->y + raiz->alto/2, raiz->ancho/2, raiz->alto/2);
        crear_arbol(raiz->hijos[2], imagen);
        raiz->hijos[3] = crear_nodo(raiz->x + raiz->ancho/2, raiz->y + raiz->alto/2, raiz->ancho/2, raiz->alto/2);
        crear_arbol(raiz->hijos[3], imagen);
    }
    else {
        raiz->L_promedio = imagen->pixels[raiz->y][raiz->x].L;
        raiz->a_promedio = imagen->pixels[raiz->y][raiz->x].a;
        raiz->b_promedio = imagen->pixels[raiz->y][raiz->x].b;
    }
}

double calcular_promedio(double valor1, double valor2, double valor3, double valor4) {
    double suma = 0;
    suma += valor1;
    suma += valor2;
    suma += valor3;
    suma += valor4;
    return suma/4;
}

void llenar_promedios(Nodo* raiz) {
    if (raiz->ancho > 1 && raiz->alto > 1){
        llenar_promedios(raiz->hijos[0]);
        llenar_promedios(raiz->hijos[1]);
        llenar_promedios(raiz->hijos[2]);
        llenar_promedios(raiz->hijos[3]);
        raiz->L_promedio = calcular_promedio(raiz->hijos[0]->L_promedio, raiz->hijos[1]->L_promedio, raiz->hijos[2]->L_promedio, raiz->hijos[3]->L_promedio);
        raiz->a_promedio = calcular_promedio(raiz->hijos[0]->a_promedio, raiz->hijos[1]->a_promedio, raiz->hijos[2]->a_promedio, raiz->hijos[3]->a_promedio);
        raiz->b_promedio = calcular_promedio(raiz->hijos[0]->b_promedio, raiz->hijos[1]->b_promedio, raiz->hijos[2]->b_promedio, raiz->hijos[3]->b_promedio);
    }
}

void calcular_suma2(Nodo* nodo){
    if (nodo->ancho <= 1 && nodo->alto <= 1) {
        nodo -> suma2_L = pow(nodo -> L_promedio, 2);
        nodo -> suma2_a = pow(nodo -> a_promedio, 2);
        nodo -> suma2_b = pow(nodo -> b_promedio, 2);          
    }
    else {
        calcular_suma2(nodo -> hijos[0]);
        calcular_suma2(nodo -> hijos[1]);
        calcular_suma2(nodo -> hijos[2]);
        calcular_suma2(nodo -> hijos[3]);
        nodo -> suma2_L = nodo -> hijos[0] -> suma2_L + nodo -> hijos[1] -> suma2_L + nodo -> hijos[2] -> suma2_L + nodo -> hijos[3] -> suma2_L;
        nodo -> suma2_a = nodo -> hijos[0] -> suma2_a + nodo -> hijos[1] -> suma2_a + nodo -> hijos[2] -> suma2_a + nodo -> hijos[3] -> suma2_a;
        nodo -> suma2_b = nodo -> hijos[0] -> suma2_b + nodo -> hijos[1] -> suma2_b + nodo -> hijos[2] -> suma2_b + nodo -> hijos[3] -> suma2_b;
    }
}

void llenar_desvestas(Nodo* nodo) {
    if (nodo->ancho > 1 && nodo->alto > 1) {
        nodo->L_desvesta = sqrt(nodo->suma2_L / pow(nodo->ancho, 2) - pow(nodo->L_promedio, 2));
        nodo->a_desvesta = sqrt(nodo->suma2_a / pow(nodo->ancho, 2) - pow(nodo->a_promedio, 2));
        nodo->b_desvesta = sqrt(nodo->suma2_b / pow(nodo->ancho, 2) - pow(nodo->b_promedio, 2));
        nodo -> gamma = (nodo -> L_desvesta + nodo -> a_desvesta + nodo -> b_desvesta)/3;
        llenar_desvestas(nodo -> hijos[0]);
        llenar_desvestas(nodo -> hijos[1]);
        llenar_desvestas(nodo -> hijos[2]);
        llenar_desvestas(nodo -> hijos[3]);
    }
}

void filtro_alpha(Nodo* raiz, double alpha, Image* imagen) {
    if (raiz->gamma <= alpha) {
        img_square_paint(
            imagen, // Imagen donde se pintara el cuadrado
            raiz->y, // Fila donde comienza el cuadrado
            raiz->x, // Columna donde comienza el cuadrado
            raiz->ancho, // Largo del lado del cuadrado
            (Color) {.L = raiz->L_promedio, .a = raiz->a_promedio, .b = raiz->b_promedio}
        );
    }
    else {
        filtro_alpha(raiz->hijos[0], alpha, imagen);
        filtro_alpha(raiz->hijos[1], alpha, imagen);
        filtro_alpha(raiz->hijos[2], alpha, imagen);
        filtro_alpha(raiz->hijos[3], alpha, imagen);
    }
}

int cantidad_hojas(Nodo* raiz, int alpha) {
    if (raiz->gamma <= alpha) {
        return 1;
    }
    else {
        return cantidad_hojas(raiz->hijos[0], alpha) + cantidad_hojas(raiz->hijos[1], alpha) + cantidad_hojas(raiz->hijos[2], alpha) + cantidad_hojas(raiz->hijos[3], alpha);
    }
}

int minimo_alpha(Nodo* raiz, int alpha, int inicio, int fin, int maximo_hojas) {
    int h = cantidad_hojas(raiz, alpha);

    if (h <= maximo_hojas) {
        if (cantidad_hojas(raiz, alpha -1) <= maximo_hojas) {
            return minimo_alpha(raiz, (alpha+inicio)/2, inicio, alpha, maximo_hojas);
        }
        else {
            return alpha;
        }
    }
    else {
        return minimo_alpha(raiz, (alpha+fin)/2, alpha, fin, maximo_hojas);
    }
}

void free_arbol(Nodo* raiz) {
    if (raiz->hijos[0] != NULL) {
        free_arbol(raiz->hijos[0]);
    }
    if (raiz->hijos[1] != NULL) {
        free_arbol(raiz->hijos[1]);
    }
    if (raiz->hijos[2] != NULL) {
        free_arbol(raiz->hijos[2]);
    }
    if (raiz->hijos[3] != NULL) {
        free_arbol(raiz->hijos[3]);
    }
    free(raiz);
}