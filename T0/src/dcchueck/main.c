#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

typedef struct guerrero_t {
  int id;
  int vida;
  int dano_base;
  int* arsenal;
  int faccion;
  struct guerrero_t* siguiente; // Puntero que apunta a la dirección de memoria del siguiente guerrero
  struct guerrero_t* anterior; // Puntero que apunta a la dirección de memoria del guerrero anterior
  int capacidad_arsenal;
} Guerrero;

typedef struct escuadron_t {
  int id;
  int cantidad_escuadrones;
  Guerrero* primer_guerrero; // Puntero que apunta a la dirección de memoria del primer guerrero
  Guerrero* ultimo_guerrero; // Puntero que apunta a la dirección de memoria del ultimo guerrero
} Escuadron;

Guerrero* crear_guerrero(int id, int vida, int dano_base, int arsenal, int faccion) {
  Guerrero* guerrero = calloc(1, sizeof(Guerrero));
  guerrero->id = id;
  guerrero->vida = vida;
  guerrero->dano_base = dano_base;
  guerrero->arsenal = calloc(arsenal, sizeof(int));
  guerrero->capacidad_arsenal = arsenal;
  guerrero->faccion = faccion;
  guerrero->siguiente = NULL;
  guerrero->anterior = NULL;
  return guerrero;
}

Escuadron* crear_escuadrones(int cantidad_escuadrones) {
  Escuadron* escuadrones = calloc(cantidad_escuadrones, (sizeof(Escuadron)));
  for (int i = 0; i < cantidad_escuadrones; i++) {
    escuadrones[i].id = i;
    escuadrones[i].cantidad_escuadrones = cantidad_escuadrones;
    escuadrones[i].primer_guerrero = NULL;
    escuadrones[i].ultimo_guerrero = NULL;
  }
  return escuadrones;
}

void mostrar_guerreros(Escuadron* ejercito) {
  for (int i = 0; i < ejercito->cantidad_escuadrones; i++) {
      Escuadron* escuadron = &ejercito[i];
      Guerrero* guerrero = escuadron->primer_guerrero;
      printf("Escuadron %d: ", escuadron->id);
      while (guerrero != NULL) {
          printf("%d ->", guerrero->id);
          guerrero = guerrero->siguiente;
      }
      printf(" \n");
  }
}

void insertar_guerrero(Escuadron* escuadron, Guerrero* guerrero) {
  if (escuadron->primer_guerrero == NULL) {
    escuadron->primer_guerrero = guerrero;
    escuadron->ultimo_guerrero = guerrero;
    guerrero->siguiente = NULL;
    guerrero->anterior = NULL;
  }
  else {
    guerrero->anterior = escuadron->ultimo_guerrero;
    escuadron->ultimo_guerrero->siguiente = guerrero;
    escuadron->ultimo_guerrero = guerrero;
    guerrero->siguiente = NULL;
  }
}

int equipar_artefacto(Guerrero* guerrero, int bonus) {
  for (int i = 0; i < guerrero->capacidad_arsenal; i++) {
    if (guerrero->arsenal[i] == 0) {
      guerrero->arsenal[i] = bonus;
      return 0;
    }
  }
  return 1;
}

void orden_ejercito(Escuadron* ejercito, FILE *output_file) {
  int** conteo = calloc(ejercito[0].cantidad_escuadrones, sizeof(int*));
  for (int k = 0; k < ejercito[0].cantidad_escuadrones; k++) {
    conteo[k] = calloc(2, sizeof(int));
  }
  for (int i = 0; i < ejercito[0].cantidad_escuadrones; i++) {
    int contador = 0;
    if (ejercito[i].primer_guerrero != NULL) {
        Guerrero* guerrero = ejercito[i].primer_guerrero;
        while (guerrero != NULL) {
          Guerrero* siguiente_guerrero = guerrero->siguiente; 
          contador ++;
          guerrero = siguiente_guerrero; 
        }
      }
    conteo[i][0] = i; 
    conteo[i][1] = contador;
  }
  for (int i = 1; i < ejercito[0].cantidad_escuadrones; i++) { //insertion sort
    int j = i;
    while (j > 0 && conteo[j][1] > conteo[j-1][1]) {
      int* temp = conteo[j];
      conteo[j] = conteo[j-1];
      conteo[j-1] = temp;
      j--;
    }
  }
  for (int j = 0; j < ejercito[0].cantidad_escuadrones; j++) {
    fprintf(output_file, "\tESCUADRON %i %i\n", conteo[j][0], conteo[j][1]);
  }
  for (int l = 0; l < ejercito[0].cantidad_escuadrones; l++) {
    free(conteo[l]);
  }
  free(conteo);
}

Guerrero* sacar_guerrero(Escuadron* escuadron, int guerreroID, int ejercitoID){
  Guerrero* guerrero = escuadron->primer_guerrero;
  while (guerrero != NULL) {
    Guerrero* siguiente_guerrero = guerrero->siguiente; // Almacenamos el siguiente guerrero antes de liberar la memoria
    if (guerrero->id == guerreroID) {
      if (guerrero->anterior == NULL && guerrero->siguiente == NULL) {
        escuadron->primer_guerrero = NULL;
        escuadron->ultimo_guerrero = NULL;
      }
      else if (guerrero->anterior == NULL) {
        escuadron->primer_guerrero = guerrero->siguiente;
        guerrero->siguiente->anterior = NULL;
      }
      else if (guerrero->siguiente == NULL) {
        escuadron->ultimo_guerrero = guerrero->anterior;
        guerrero->anterior->siguiente = NULL;
      }
      else {
        guerrero->anterior->siguiente = guerrero->siguiente;
        guerrero->siguiente->anterior = guerrero->anterior;
      }
      return guerrero;
    }
    guerrero = siguiente_guerrero; // Avanzamos al siguiente guerrero
  }
  return guerrero; //retorna NULL si no encuentra al guerrero
}

int contar_guerreros(Escuadron* escuadron) {
  int contador = 0;
  if (escuadron->primer_guerrero != NULL) {
    Guerrero* guerrero = escuadron->primer_guerrero;
    while (guerrero != NULL) {
      contador ++;
      Guerrero* siguiente_guerrero = guerrero->siguiente;
      guerrero = siguiente_guerrero;
    }
    return contador;
  }
  return 1000000000;  //numero alto para que no sea un minimo tentativo
}

int contar_ataque(Escuadron* escuadron, FILE *output_file) {
  int contador = 0;
  if (escuadron->primer_guerrero != NULL) {
    Guerrero* guerrero = escuadron->primer_guerrero;
    while (guerrero != NULL) {
      Guerrero* siguiente_guerrero = guerrero->siguiente;
      contador += guerrero->dano_base;
      guerrero = siguiente_guerrero;
    }
  }
  return contador;
}

int mejor_artefacto(Guerrero* guerrero, int maximo_arsenal) {
  int posicion = 0;
  for (int i = 0; i < guerrero->capacidad_arsenal; i++) {
    if (guerrero->arsenal[i] > maximo_arsenal) {
      maximo_arsenal = guerrero->arsenal[i];
      posicion = i;
    }
  }
  guerrero->arsenal[posicion] = 0;
  return maximo_arsenal;
}

int main(int argc, char **argv) {
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv)) {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }
  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");
  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");
  /* Leemos la cantidad de escuadrones en el primer ejercito */
  int S_SQUADRON_COUNT;
  fscanf(input_file, "%d", &S_SQUADRON_COUNT);
  /* Leemos la cantidad de escuadrones en el segundo ejercito */
  int F_SQUADRON_COUNT;
  fscanf(input_file, "%d", &F_SQUADRON_COUNT);

  Escuadron** ejercitos = calloc(2, sizeof(Escuadron*)); // Creamos un arreglo de 2 escuadrones
  ejercitos[0] = crear_escuadrones(S_SQUADRON_COUNT); // Creamos los escuadrones del primer ejercito
  ejercitos[1] = crear_escuadrones(F_SQUADRON_COUNT); // Creamos los escuadrones del segundo ejercito
  
  /* Leemos la cantidad de eventos */
  int N_EVENTS;
  fscanf(input_file, "%d", &N_EVENTS);

  /* String para guardar la instrucción actual*/
  char command[32];

  for (int event = 0; event < N_EVENTS; event++) {
    /* Leemos el evento */
    fscanf(input_file, "%s", command);
    if (string_equals(command, "ENLISTAR")) {
      int ejercitoID, escuadronID, guerreroID, vidabase, danobase, faccionID, capacidadArsenal;
      fscanf(input_file, "%d %d %d %d %d %d %d", &ejercitoID, &escuadronID, &guerreroID, &vidabase, &danobase, &faccionID, &capacidadArsenal);
      if ((ejercitoID == 0 && escuadronID < S_SQUADRON_COUNT) || (ejercitoID == 1 && escuadronID < F_SQUADRON_COUNT)) {
      Guerrero* guerrero = crear_guerrero(guerreroID, vidabase, danobase, capacidadArsenal, faccionID);
      insertar_guerrero(&ejercitos[ejercitoID][escuadronID], guerrero);
      fprintf(output_file, "ENLISTADO %d %d\n", guerreroID, escuadronID);
      }
      else {
        fprintf(output_file, "EJERCITO %d ESCUADRON %d NO EXISTE\n", ejercitoID, escuadronID);
      }
    }
    else if (string_equals(command, "EQUIPAR")) {
      int bonus, ejercitoID, escuadronID, guerreroID;
      fscanf(input_file, "%d %d %d %d", &bonus, &ejercitoID, &escuadronID, &guerreroID);
      if (ejercitos[ejercitoID][escuadronID].primer_guerrero != NULL) {
        Guerrero* guerrero = ejercitos[ejercitoID][escuadronID].primer_guerrero;
        while (guerrero != NULL) {
          Guerrero* siguiente_guerrero = guerrero->siguiente; // Almacenamos el siguiente guerrero antes de liberar la memoria
          if (guerrero->id == guerreroID) {
            if (equipar_artefacto(guerrero, bonus) == 0) {
              fprintf(output_file, "ARTEFACTO %d ASIGNADO A %d\n", bonus, guerreroID);
            }
            else {
              fprintf(output_file, "ARSENAL LLENO %d\n", guerreroID);
            }
          }
          guerrero = siguiente_guerrero; // Avanzamos al siguiente guerrero
        }
      }
      else {
        printf("NO HAY GENTE EN ESCUADRON %d DE EJERCITO %d\n", escuadronID, ejercitoID);
      }
    }
    else if (string_equals(command, "CONTEO-CAMPAL")) {
      fprintf(output_file, "CONTEO-CAMPAL\n");
      int guerreros = 0;
      for (int i = 0; i <= 1; i++) {
        fprintf(output_file, "\tEJERCITO %i\n", i);
        int f0 = 0;
        int f1 = 0;
        int f2 = 0;
        for (int j = 0; j < ejercitos[i][0].cantidad_escuadrones; j++) {
          if (ejercitos[i][j].primer_guerrero != NULL) {
            Guerrero* guerrero = ejercitos[i][j].primer_guerrero;
            while (guerrero != NULL) {
              Guerrero* siguiente_guerrero = guerrero->siguiente;
              if (guerrero->faccion == 0) {
                f0++;
                guerreros++;
              }
              else if (guerrero->faccion == 1) {
                f1++;
                guerreros++;
              }
              else if (guerrero->faccion == 2) {
                f2++;
                guerreros++;
              }
              guerrero = siguiente_guerrero;
            }
          }
        }
        fprintf(output_file, "\t\tFACCION 0: %i\n", f0);
        fprintf(output_file, "\t\tFACCION 1: %i\n", f1);
        fprintf(output_file, "\t\tFACCION 2: %i\n", f2);
      }
      fprintf(output_file, "TOTAL DE GUERREROS : %i\n", guerreros);
    }
    else if (string_equals(command, "ORDEN-EJERCITO")) {
      int ejercitoID;
      fscanf(input_file, "%d", &ejercitoID);
      fprintf(output_file, "EJERCITO %d\n", ejercitoID);
      orden_ejercito(ejercitos[ejercitoID], output_file);
    }
    else if (string_equals(command, "DESERTAR")) {
      int ejercitoID, escuadronID, guerreroID;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      fprintf(output_file, "ABANDONA %d %d\n", guerreroID, ejercitoID);
      Guerrero* guerrero = sacar_guerrero(&ejercitos[ejercitoID][escuadronID], guerreroID, ejercitoID);
      free(guerrero->arsenal);
      free(guerrero);
    }
    else if (string_equals(command, "ATACA")) {
      int ejercitoID;
      fscanf(input_file, "%d", &ejercitoID);
      //buscar escuadron atacante
      int maximo1 = 0;
      int escuadron_atacante = 0;
      for (int i = 0; i < ejercitos[ejercitoID][0].cantidad_escuadrones; i++) {
        int contador = contar_ataque(&ejercitos[ejercitoID][i], output_file);
        if (contador > maximo1) {
          maximo1 = contador;
          escuadron_atacante = i; //seleccion de que escuadron ataca
        }
      }
      //buscar escuadron defensor
      int minimo = 1000000000;
      int escuadron_defensor = 0;
      for (int j = 0; j < ejercitos[1-ejercitoID][0].cantidad_escuadrones; j++) {
        int contador = contar_guerreros(&ejercitos[1-ejercitoID][j]);
        if (contador < minimo) {
          minimo = contador;
          escuadron_defensor = j; //seleccion de que escuadron defienede
        }
      }
      //buscar mejor bonus de ataque
      int maximo = 0;
      int bonus = 0;
      int maximo_arsenal = mejor_artefacto(ejercitos[ejercitoID][escuadron_atacante].primer_guerrero, maximo); //funcion que altera variables maximo y posicion (relacionadas con arsenal)
      if (ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->faccion == 0) {
        bonus = 5;
      }
      else if (ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->faccion == 1) {
        bonus = 10;
      }
      else if (ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->faccion == 2) {
        bonus = 15;
      }
      int ataque = maximo_arsenal + ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->dano_base + bonus;
      fprintf(output_file, "ATACA %d %d\n", ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->id, ejercitos[1-ejercitoID][escuadron_defensor].primer_guerrero->id);
      if (ejercitos[1-ejercitoID][escuadron_defensor].primer_guerrero->vida - ataque > 0) {
        ejercitos[1-ejercitoID][escuadron_defensor].primer_guerrero->vida -= ataque;
      }
      else {
        int guerreroID = ejercitos[1-ejercitoID][escuadron_defensor].primer_guerrero->id;
        Guerrero* guerrero = sacar_guerrero(&ejercitos[1-ejercitoID][escuadron_defensor], guerreroID, 1-ejercitoID);
        //lanza error si se queda solo un escuadron
        free(guerrero->arsenal);
        free(guerrero);
      }
      ejercitos[ejercitoID][escuadron_atacante].ultimo_guerrero->siguiente = ejercitos[ejercitoID][escuadron_atacante].primer_guerrero;
      ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->anterior = ejercitos[ejercitoID][escuadron_atacante].ultimo_guerrero;
      ejercitos[ejercitoID][escuadron_atacante].primer_guerrero = ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->siguiente;
      ejercitos[ejercitoID][escuadron_atacante].ultimo_guerrero = ejercitos[ejercitoID][escuadron_atacante].ultimo_guerrero->siguiente;
      ejercitos[ejercitoID][escuadron_atacante].ultimo_guerrero->siguiente = NULL;
      ejercitos[ejercitoID][escuadron_atacante].primer_guerrero->anterior = NULL;
    }
    else if (string_equals(command, "TRAICIONAR")) {
      int ejercitoID, escuadronID, guerreroID;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      //buscar guerrero y sacarlo
      Guerrero* guerrero = sacar_guerrero(&ejercitos[ejercitoID][escuadronID], guerreroID, ejercitoID);
      //buscar escuadron rival
      int maximo = 0;
      int escuadron_rival = 0;
      for (int j = 0; j < ejercitos[1-ejercitoID][0].cantidad_escuadrones; j++) {
        int contador = contar_guerreros(&ejercitos[1-ejercitoID][j]);
        if (contador == 1000000000) {
          contador = 0;
        }
        if (contador > maximo) {
          maximo = contador;
          escuadron_rival = j; //seleccion de escuadron al que se va
        }
      }
      //insertar el guerrero
      insertar_guerrero(&ejercitos[1-ejercitoID][escuadron_rival], guerrero);
      fprintf(output_file, "TRAICION %d\n", ejercitoID);
    }
    else if (string_equals(command, "ALTA-TRAICION")) {
      int ejercitoID, escuadronID, guerreroID;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      //escuadron rival
      int maximo = 0;
      int escuadron_rival = 0;
      for (int j = 0; j < ejercitos[1-ejercitoID][0].cantidad_escuadrones; j++) {
        int contador = contar_guerreros(&ejercitos[1-ejercitoID][j]);
        if (contador == 1000000000) {
          contador = 0;
        }
        if (contador > maximo) {
          maximo = contador;
          escuadron_rival = j; //seleccion de escuadron al que se va
        }
      }
      Guerrero* guerrero = sacar_guerrero(&ejercitos[ejercitoID][escuadronID], guerreroID, ejercitoID);
      Guerrero* siguiente_guerrero = guerrero->siguiente;
      insertar_guerrero(&ejercitos[1-ejercitoID][escuadron_rival], guerrero);
      guerrero = siguiente_guerrero;
      while (guerrero != NULL) {
        guerrero = sacar_guerrero(&ejercitos[ejercitoID][escuadronID], guerrero->id, ejercitoID);
        Guerrero* siguiente_guerrero = guerrero->siguiente;
        insertar_guerrero(&ejercitos[1-ejercitoID][escuadron_rival], guerrero);
        guerrero = siguiente_guerrero;
      }
      fprintf(output_file, "ALTA-TRAICION %d\n", ejercitoID);
    }
  }
/*  [Por implementar] Liberamos nuestras estructuras */
for (int i = 0; i < S_SQUADRON_COUNT; i++) {
  if (ejercitos[0][i].primer_guerrero != NULL) {
    Guerrero* guerrero = ejercitos[0][i].primer_guerrero;
    while (guerrero != NULL) {
      Guerrero* siguiente_guerrero = guerrero->siguiente; // Almacenamos el siguiente guerrero antes de liberar la memoria
      free(guerrero->arsenal);
      free(guerrero);
      guerrero = siguiente_guerrero; // Avanzamos al siguiente guerrero
    }
  }
}
for (int j = 0; j < F_SQUADRON_COUNT; j++) { 
  if (ejercitos[1][j].primer_guerrero != NULL) {
    Guerrero* guerrero = ejercitos[1][j].primer_guerrero;
    while (guerrero != NULL) {
      Guerrero* siguiente_guerrero = guerrero->siguiente; // Almacenamos el siguiente guerrero antes de liberar la memoria
      free(guerrero->arsenal);
      free(guerrero);
      guerrero = siguiente_guerrero; // Avanzamos al siguiente guerrero
    }
  }
}
  free(ejercitos[0]);
  free(ejercitos[1]);
  free(ejercitos);
  fclose(input_file);
  fclose(output_file);
  return 0;
}
