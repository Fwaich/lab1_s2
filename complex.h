#pragma once
#include "vector.h"

typedef struct Complex{
    int Re;
    int Im;
}Complex;

Vector* new_complex_vector(Vtable* t, int sz);

void delete_complex_vector(Vector** v);

void fill_complex_vector(Vector* v);

Vector* add_complex(Vector* v1, Vector* v2);

Vector* complex_dot_product(Vector* v1, Vector* v2);

char* to_char_complex(Vector* v);

Vtable* create_complex();
