#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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

void delete_complex_vector(Vector** v){
    
    if ((*v)->vec) { 
        if ((*v)->vec->data) {
            free((*v)->vec->data);
            (*v)->vec->data = NULL;
        }
        free((*v)->vec);
        (*v)->vec = NULL;
    }

    free(*v);
    *v = NULL;
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

Vector* add_complex(Vector* v1, Vector* v2){
    Vector* v_res = v1->table->new(v1->table, v1->vec->dim);
    Complex* v1_data = (Complex *)v1->vec->data;
    Complex* v2_data = (Complex *)v2->vec->data;
    Complex* res_data = (Complex *)v_res->vec->data;

    for (int i = 0; i < v1->vec->dim; i++){
        res_data[i].Re = v1_data[i].Re + v2_data[i].Re;
        res_data[i].Im = v1_data[i].Im + v2_data[i].Im; 
    }

    return v_res;
}


Vector* complex_dot_product(Vector* v1, Vector* v2){
    Vector* v_res = v1->table->new(v1->table, 1);
    Complex* v1_data = (Complex *)v1->vec->data;
    Complex* v2_data = (Complex *)v2->vec->data;
    Complex* res_data = (Complex *)v_res->vec->data;

    int Re_result = 0;
    int Im_result = 0;
    for (int i = 0; i < v1->vec->dim; i++){
        int Re = (v1_data[i].Re * v2_data[i].Re) - (v1_data[i].Im * v2_data[i].Im);
        int Im = (v1_data[i].Re * v2_data[i].Im) + (v2_data[i].Re * v1_data[i].Im);
        Re_result += Re;
        Im_result += Im;
    }

    res_data->Re = Re_result;
    res_data->Im = Im_result;


    return v_res;
}

void from_array_complex(Vector* v, int num, ...){
    Complex* v_data = (Complex *)v->vec->data;
    va_list valist;
    va_start(valist, num);
    for (int i = 0; i < num / 2; i++) {
        v_data[i].Re = va_arg(valist, int);
        v_data[i].Im = va_arg(valist, int);
    }

    va_end(valist);
}

char* to_char_complex(Vector* v){

    Complex* v_data = (Complex *)v->vec->data;
    int total_size = 1;

    for (int i = 0; i < v->vec->dim; i++){
        total_size += snprintf(NULL, 0, "(%d + %di) ", v_data[i].Re, abs(v_data[i].Im));
    }

    char* v_str = (char *)malloc(total_size);
    char* ptr = v_str;
    for (int i = 0; i < v->vec->dim; i++){
        char sign = (v_data[i].Im < 0) ? '-' : '+';
        ptr += sprintf(ptr, "(%d %c %di) ", v_data[i].Re, sign, abs(v_data[i].Im));
    }

    return v_str;
}


Vtable* create_complex(){
    Vtable* complex_table = (Vtable *)malloc(sizeof(Vtable));
    complex_table->new = new_complex_vector;
    complex_table->delete = delete_complex_vector;
    complex_table->fill_vector = fill_complex_vector;
    complex_table->add = add_complex; 
    complex_table->dot_product = complex_dot_product;
    complex_table->from_array = from_array_complex;
    complex_table->to_char = to_char_complex;
    return complex_table;
}