#pragma once
#include "vector.h"

Vector* new_int_vector(Vtable* t, int sz);

void delete_int_vector(Vector* v);

Vtable* create_int();