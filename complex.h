#pragma once
#include "vector.h"

typedef struct Complex{
    int Re;
    int Im;
}Complex;

Vector* new_complex_vector(Vtable* t, int sz);

void delete_complex_vector(Vector* v);

void fill_complex_vector(Vector* v);

Vector* add_complex(Vector* v1, Vector* v2);

Vtable* create_complex();
