#include "hash.h"
#include <string.h>

HashItem* create_hash_item(int largo, char* value) {
    HashItem* item = calloc(1, sizeof(HashItem));
    item->largo = largo;
    item->veces = 1;
    item->next = NULL;
    char* value_copy = calloc(strlen(value) + 1, sizeof(char));
    strcpy(value_copy, value);
    item->value = value_copy;
    return item;
}

int hash_function(int largo, int range) {
    //función modulo, en donde range es el largo de la tabla
    return largo % range;
}

//para que sirve el value? ver si se elimina o no
void insert_or_update(HashItem **table, int largo, char *value, int table_size){
    int table_index = hash_function(largo, table_size);
    HashItem *item = table[table_index];
    if (item == NULL) {
        item = create_hash_item(largo, value);
        table[table_index] = item;
    } else {
        while (item->next != NULL) {
            if (strcmp(item->value, value) == 0) {
                item->veces += 1;
                return;
            }
            item = item->next;
        }
        //como el último no se revisa, lo reviso acá
        if (strcmp(item->value, value) == 0) {
            item->veces += 1;
            return;
        }
        //si no está, se agrega
        item->next = create_hash_item(largo, value);
    }
}

int fetch_value(HashItem **table, int largo, char *value, int table_size) {
    int table_index = hash_function(largo, table_size);
    HashItem *item = table[table_index];
    while (item != NULL) {
        if (strcmp(item->value, value) == 0) {
            return item->veces;
        }
        item = item->next;
    }
    return 0;
}

void free_hash_table(HashItem **table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        HashItem *item = table[i];
        while (item != NULL) {
            HashItem *next = item->next;
            free(item->value);
            free(item);
            item = next;
        }
    }
    free(table);
}