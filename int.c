#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "int.h"

Vector* new_int_vector(Vtable* t, int sz){
    Vector* v = (Vector *)malloc(sizeof(Vector));
    Vector_data* v_data = (Vector_data *)malloc(sizeof(Vector_data));
    v->vec = v_data;
    v->table = t;
    v->vec->dim = sz;
    v->vec->data = malloc(sz * sizeof(int));
    return v;
}

void delete_int_vector(Vector* v){
    if (!v) return;
    if (v->vec) { 
        if (v->vec->data) {
            free(v->vec->data);
            v->vec->data = NULL;
        }
        free(v->vec);
        v->vec = NULL;
    }

    free(v);
}

void fill_int_vector(Vector* v){
    for (int i = 0; i < v->vec->dim; i++){
        int value;
        scanf("%d", &value);
        memcpy((char *)v->vec->data + i * sizeof(int), &value, sizeof(int));
    }
}

char* to_char_int(Vector* v) {
    if (!v || !v->vec || !v->vec->data) return NULL;

    int* data = (int*)v->vec->data;
    int max_len = v->vec->dim * 10;
    char* v_str = (char*)malloc(max_len);

    v_str[0] = '\0';

    for (int i = 0; i < v->vec->dim; i++) {
        char el_str[10];
        sprintf(el_str, "%d ", data[i]);
        strcat(v_str, el_str);
    }

    return v_str;
}

Vtable* create_int(){
    Vtable* int_table = (Vtable *)malloc(sizeof(Vtable));
    int_table->new = new_int_vector;
    int_table->delete = delete_int_vector;
    int_table->fill_vector = fill_int_vector;
    int_table->to_char = to_char_int;
    return int_table;
}

