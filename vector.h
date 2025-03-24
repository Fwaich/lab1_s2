#pragma once

typedef struct Vector Vector;
typedef struct Vtable Vtable;

typedef struct {
    unsigned short dim;
    void* data;
}Vector_data;

typedef struct Vtable{
    Vector* (*new)(Vtable* t, int sz);
    void (*delete)(Vector* v);
    void (*fill_vector)(Vector* v);
    void (*from_array)(Vector* v, int num, ...);
    Vector* (*add)(Vector* v1, Vector* v2);
    Vector* (*dot_product)(Vector* v1, Vector* v2);
    char* (*to_char)(Vector* v);
}Vtable;
    
typedef struct Vector{
    Vector_data* vec;
    Vtable* table;
}Vector;

Vector* new(Vtable* t, int sz);

void delete_vector(Vector* v);

void fill_vector(Vector* v);

Vector* add(Vector* v1, Vector* v2);

Vector* dot_product(Vector* v1, Vector* v2);

char* to_char(Vector* v);