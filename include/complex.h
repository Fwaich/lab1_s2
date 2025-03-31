#pragma once
#include "vector.h"

typedef struct Complex{
    int Re;
    int Im;
}Complex;

Vecptr new_complex_vector(Vtable* t, int sz);

void delete_complex_vector(Vecptr* v);

void fill_complex_vector(Vecptr v);

Vecptr add_complex(Vecptr v1, Vecptr v2);

Vecptr complex_dot_product(Vecptr v1, Vecptr v2);

char* to_char_complex(Vecptr v);

Vtable* create_complex();
