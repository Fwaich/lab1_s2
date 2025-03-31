#pragma once
#include "vector.h"

Vecptr new_int_vector(Vtable* t, int sz);

void delete_int_vector(Vecptr* v);

void fill_int_vector(Vecptr v);

Vecptr add_int(Vecptr v1, Vecptr v2);

Vecptr int_dot_product(Vecptr v1, Vecptr v2);

void from_array_int(Vecptr v, int num, ...);

char* to_char_int(Vecptr v);

Vtable* create_int();