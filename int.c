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
    if(!v) return;
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

Vector* add_int(Vector* v1, Vector* v2){
    Vector* v_res = v1->table->new(v1->table, v1->vec->dim);
    int* v1_data = (int *)v1->vec->data;
    int* v2_data = (int *)v2->vec->data;

    for (int i = 0; i < v1->vec->dim; i++){
        int result = v1_data[i] + v2_data[i];
        ((int*)v_res->vec->data)[i] = result;
    }

    return v_res;
}

Vector* int_dot_product(Vector* v1, Vector* v2){
    Vector* v_res = v1->table->new(v1->table, 1);
    int* v1_data = (int *)v1->vec->data;
    int* v2_data = (int *)v2->vec->data;
    int result = 0;
    
    for (int i = 0; i < v1->vec->dim; i++){
        result += v1_data[i] * v2_data[i];
    }
    ((int*)v_res->vec->data)[0] = result;

    return v_res;
}

char* to_char_int(Vector* v) {
    if (!v || !v->vec || !v->vec->data) return NULL;

    int* data = (int*)v->vec->data;
    int total_size = 1;
    
    for (int i = 0; i < v->vec->dim; i++) {
        total_size += snprintf(NULL, 0, "%d ", data[i]);
    }

    char* v_str = (char*)malloc(total_size);
    if (!v_str) return NULL;

    char* ptr = v_str;
    for (int i = 0; i < v->vec->dim; i++) {
        ptr += sprintf(ptr, "%d ", data[i]);
    }

    return v_str;
}

Vtable* create_int(){
    Vtable* int_table = (Vtable *)malloc(sizeof(Vtable));
    int_table->new = new_int_vector;
    int_table->delete = delete_int_vector;
    int_table->fill_vector = fill_int_vector;
    int_table->to_char = to_char_int;
    int_table->add = add_int; 
    int_table->dot_product = int_dot_product;
    return int_table;
}

