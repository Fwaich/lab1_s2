#pragma once


typedef struct Vector Vector;
typedef struct Vtable Vtable;
typedef Vector* Vecptr;

typedef struct {
    unsigned short dim;
    void* data;
}Vector_data;

typedef struct Vtable{
    Vecptr (*new)(Vtable* t, int sz);
    void (*delete)(Vecptr* v);
    void (*fill_vector)(Vecptr v);
    void (*from_array)(Vecptr v, int num, ...);
    Vecptr (*add)(Vecptr v1, Vecptr v2);
    Vecptr (*dot_product)(Vecptr v1, Vecptr v2);
    char* (*to_char)(Vecptr v);
}Vtable;
    
typedef struct Vector{
    Vector_data* vec;
    Vtable* table;
}Vector;

Vecptr new(Vtable* t, int sz);

void delete_vector(Vecptr* v);

void fill_vector(Vecptr v);

Vecptr add(Vecptr v1, Vecptr v2);

Vecptr dot_product(Vecptr v1, Vecptr v2);

char* to_char(Vecptr v);