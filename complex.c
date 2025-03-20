#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "complex.h"

Vector* new_complex_vector(Vtable* t, int sz){
    Vector* v = (Vector *)malloc(sizeof(Vector));
    Vector_data* v_data = (Vector_data *)malloc(sizeof(Vector_data));
    v->vec = v_data;
    v->table = t;
    v->vec->dim = sz;
    v->vec->data = (Complex *)malloc(sz * sizeof(Complex));
    return v;
}

void delete_complex_vector(Vector* v){

    if(!v) return;
    if (v->vec) { 
        if (v->vec->data) {
            free(v->vec->data);
            v->vec->data = NULL;
        }
        free(v->vec);
        v->vec = NULL;
    }

    free(v);

}

void fill_complex_vector(Vector* v){
    for (int i = 0; i < v->vec->dim; i++){

        printf("Re[%d]: ", i);
        int value_re;
        scanf("%d", &value_re);

        printf("   Im[%d]: ", i);
        int value_im;
        scanf("%d", &value_im);

        void* dest = (char *)v->vec->data + i * sizeof(Complex); 
        Complex tmp = {value_re, value_im};

        memcpy((char *)v->vec->data + i * sizeof(Complex), &tmp, sizeof(Complex));
    }
}



Vtable* create_complex(){
    Vtable* complex_table = (Vtable *)malloc(sizeof(Vtable));
    complex_table->new = new_complex_vector;
    complex_table->delete = delete_complex_vector;
    complex_table->fill_vector = fill_complex_vector;
    // complex_table->to_char = to_char_complex;
    // complex_table->add = add_complex; 
    // complex_table->dot_product = complex_dot_product;
    return complex_table;
}