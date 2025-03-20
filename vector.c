#include <stdlib.h>
#include "vector.h"
#include <stdio.h>

Vector* new(Vtable* t, int sz) {
    return t->new(t, sz);
}

void delete_vector(Vector* v) {
    if (!v) return; 
    v->table->delete(v);
}

void fill_vector(Vector* v){
    if(!v) return;
    return v->table->fill_vector(v);
}

Vector* add(Vector* v1, Vector* v2){
    if (!v1 || !v2 || v1->table != v2->table ||
        v1->vec->dim != v2->vec->dim){
        printf("Разные типы или размеры\n");
        return NULL;
    }

    return v1->table->add(v1, v2);
}

Vector* dot_product(Vector* v1, Vector* v2){
    if (!v1 || !v2 || v1->table != v2->table ||
        v1->vec->dim != v2->vec->dim){
        printf("Разные типы или размеры\n");
        return NULL;
    }

    return v1->table->dot_product(v1, v2);
}

char* to_char(Vector* v){
    if(!v) return NULL;
    return v->table->to_char(v);
}