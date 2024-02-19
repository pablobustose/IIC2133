#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct hashitem_t {
    int largo;
    int veces;
    char* value;
    struct hashitem_t *next;
} HashItem;


int hash_function(int key, int range);

HashItem* create_hash_item(int largo, char* value);

void insert_or_update(HashItem **table, int largo, char* value, int table_size);

int fetch_value(HashItem **table, int largo, char* value, int table_size);

void free_hash_table(HashItem **table, int table_size);