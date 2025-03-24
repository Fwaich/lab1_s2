#include <stdlib.h>
#include "vector.h"
#include <stdio.h>
#include <errno.h>
#include <assert.h>

Vector* new(Vtable* t, int sz) {
    if (sz <= 0 || !t){
        errno = EINVAL;
        return NULL;
    }
    return t->new(t, sz);
}

void delete_vector(Vector** v) {
    if (!(*v)) return; 
    (*v)->table->delete(v);
}

void fill_vector(Vector* v){
    if(!v) {
        errno = EINVAL;
        return;
    }
    return v->table->fill_vector(v);
}

Vector* add(Vector* v1, Vector* v2){
    if (!v1 || !v2) {
        fprintf(stderr, "Не инициализирован(-ы) вектор(-ы)\n");
        errno = EPERM;
        return NULL;
    } 

    if(v1->table != v2->table){
        fprintf(stderr, "Разные типы векторов\n");
        errno = EPERM;
        return NULL;
    }

    if(v1->vec->dim != v2->vec->dim){
        fprintf(stderr, "Разные размеры векторов\n");
        errno = EPERM;
        return NULL;
    }

    return v1->table->add(v1, v2);
}

Vector* dot_product(Vector* v1, Vector* v2){
    if (!v1 || !v2) {
        fprintf(stderr, "Векторы не инициализированы\n");
        errno = EPERM;
        return NULL;
    } 

    if(v1->table != v2->table){
        fprintf(stderr, "Разные типы");
        errno = EPERM;
        return NULL;
    }

    if(v1->vec->dim != v2->vec->dim){
        fprintf(stderr, "Разные размеры векторов\n");
        errno = EPERM;
        return NULL;
    }

    return v1->table->dot_product(v1, v2);
}

char* to_char(Vector* v){
    if(!v) return NULL;
    return v->table->to_char(v);
}