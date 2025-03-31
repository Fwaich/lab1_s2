#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "int.h"
#include "complex.h"

void test_new(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vecptr vec = NULL;

    int expected_size = 5;

    vec = new(int_type, expected_size);
    assert(vec != NULL);
    assert(vec->vec != NULL);
    assert(vec->vec->data != NULL);
    assert(vec->vec->dim == expected_size);
    delete_vector(&vec);

    vec = new(complex_type, expected_size);
    assert(vec != NULL);
    assert(vec->vec != NULL);
    assert(vec->vec->data != NULL);
    assert(vec->vec->dim == expected_size);
    delete_vector(&vec);

    printf("new(): SUCCESS\n");
    free(int_type);
    free(complex_type);
}

void test_delete(){
    Vtable* int_type = create_int();
    Vecptr vec = NULL;

    vec = new(int_type, 5);
    delete_vector(&vec);
    assert(vec == NULL);

    printf("delete_vector(&): SUCCESS\n");
    free(int_type);
}

void test_add(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vecptr vec1 = NULL;
    Vecptr vec2 = NULL;
    Vecptr vec_res = NULL;

    fprintf(stderr, "add():\n");

    //Векторы не инициализированы
    vec_res = add(vec1, vec2);
    assert(vec_res == NULL);

    //Векторы разной длинны
    vec1 = new(int_type, 2);
    vec2 = new(int_type, 3);
    vec_res = add(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(&vec1);
    delete_vector(&vec2);

    //Векторы разных типов
    vec1 = new(int_type, 2);
    vec2 = new(complex_type, 2);
    vec_res = add(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(&vec1);
    delete_vector(&vec2);

    //Проверка результатов сложения
    int size = 5;
    int expected_result_int[] = {7, 9, 11, 13, 15};
    vec1 = new(int_type, size);
    vec2 = new(int_type, size);
    vec1->table->from_array(vec1, size, 1, 2, 3, 4, 5);
    vec2->table->from_array(vec2, size, 6, 7, 8, 9, 10);
    vec_res = add(vec1, vec2);
    assert(vec_res != NULL);
    assert(vec_res->table == vec1->table);
    assert(vec_res->vec->dim == vec1->vec->dim);
    int* res_data_int = (int *)vec_res->vec->data;
    for (int i = 0; i < vec_res->vec->dim; i++){
        assert(res_data_int[i] == expected_result_int[i]);
    }
    delete_vector(&vec1);
    delete_vector(&vec2);
    delete_vector(&vec_res);

    size = 3;
    Complex expected_result_complex[] = {{7, 9}, {11, 13}, {15, 23}};
    vec1 = new(complex_type, size);
    vec2 = new(complex_type, size);
    vec1->table->from_array(vec1, size * 2, 1, 2, 3, 4, 5, 11);
    vec2->table->from_array(vec2, size * 2, 6, 7, 8, 9, 10, 12);
    vec_res = add(vec1, vec2);
    assert(vec_res != NULL);
    assert(vec_res->table == vec1->table);
    assert(vec_res->vec->dim == vec1->vec->dim);
    Complex* res_data_complex = (Complex *)vec_res->vec->data;
    for (int i = 0; i < vec_res->vec->dim; i++){
        assert(res_data_complex[i].Re == expected_result_complex[i].Re);
        assert(res_data_complex[i].Im == expected_result_complex[i].Im);
    }
    delete_vector(&vec1);
    delete_vector(&vec2);
    delete_vector(&vec_res);

    printf("add(): SUCCESS\n");
    free(int_type);
    free(complex_type);
}

void test_dot_product(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vecptr vec1 = NULL;
    Vecptr vec2 = NULL;
    Vecptr vec_res = NULL;

    fprintf(stderr, "dot_product():\n");

    //Векторы не инициализированы
    vec_res = dot_product(vec1, vec2);
    assert(vec_res == NULL);

    //Векторы разной длинны
    vec1 = new(complex_type, 2);
    vec2 = new(complex_type, 3);
    vec_res = dot_product(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(&vec1);
    delete_vector(&vec2);

    //Векторы разных типов
    vec1 = new(int_type, 2);
    vec2 = new(complex_type, 2);
    vec_res = dot_product(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(&vec1);
    delete_vector(&vec2);

    //Проверка результатов произведения
    int size = 5;
    vec1 = new(int_type, size);
    vec2 = new(int_type, size);
    vec1->table->from_array(vec1, size, 1, 2, 3, 4, 5);
    vec2->table->from_array(vec2, size, 6, 7, 8, 9, 10);
    int expected_result_int = 130;
    vec_res = dot_product(vec1, vec2);
    assert(vec_res->vec->dim == 1);
    assert(((int *)vec_res->vec->data)[0] == expected_result_int);
    delete_vector(&vec1);
    delete_vector(&vec2);
    delete_vector(&vec_res);

    size = 3;
    vec1 = new(complex_type, size);
    vec2 = new(complex_type, size);
    vec1->table->from_array(vec1, size * 2, 1, 2, 3, 4, 5, 11);
    vec2->table->from_array(vec2, size * 2, 6, 7, 8, 9, 10, 12);
    Complex expected_result_complex = {-102, 248};
    vec_res = dot_product(vec1, vec2);
    assert(vec_res->vec->dim == 1);
    assert(((Complex *)vec_res->vec->data)[0].Re == expected_result_complex.Re);
    assert(((Complex *)vec_res->vec->data)[0].Im == expected_result_complex.Im);
    delete_vector(&vec1);
    delete_vector(&vec2);
    delete_vector(&vec_res);

    printf("dot_product(): SUCCESS\n");
    free(int_type);
    free(complex_type);    
}

void test_to_char(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vecptr vec = NULL;
    char* output = NULL;

    vec = new(int_type, 3);
    vec->table->from_array(vec, 3, 1, 2, 3);
    output = to_char(vec);
    char* expected_result_int = "1 2 3 ";
    assert(strcmp(output, expected_result_int) == 0);
    delete_vector(&vec);
    free(output);

    vec = new(complex_type, 2);
    vec->table->from_array(vec, 4, 1, 2, 3, -4);
    output = to_char(vec);
    char* expected_result_complex = "(1 + 2i) (3 - 4i) ";
    assert(strcmp(output, expected_result_complex) == 0);
    delete_vector(&vec);
    free(output);

    printf("to_char(): SUCCESS\n");
    delete_vector(&vec);
    free(int_type);
    free(complex_type);
}

int main() {
    test_new();
    test_delete();
    test_add();
    test_dot_product();
    test_to_char();

    printf("\nAll tests passed\n");
}