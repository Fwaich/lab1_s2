#pragma once
#include "vector.h"

Vector* new_int_vector(Vtable* t, int sz);

void delete_int_vector(Vector* v);

void fill_int_vector(Vector* v);

Vector* add_int(Vector* v1, Vector* v2);

Vector* int_dot_product(Vector* v1, Vector* v2);

char* to_char_int(Vector* v);

Vtable* create_int();