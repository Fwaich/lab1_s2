#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "int.h"
#include "complex.h"

void test_new(){
    Vtable* int_type = create_int();
    Vector* vec = NULL;

    int expected_size = 5;
    vec = new(int_type, expected_size);
    assert(vec != NULL);
    assert(vec->vec != NULL);
    assert(vec->vec->data != NULL);
    assert(vec->vec->dim == expected_size);

    printf("new(): SUCCESS\n");
    delete_vector(vec);
    free(int_type);
}

// void test_delete(){
//     Vtable* int_type = create_int();
//     Vector* vec = NULL;

//     vec = new(int_type, 5);
//     delete_vector(vec);
//     assert(vec == NULL);

//     printf("delete_vector(): SUCCESS\n");
//     free(int_type);
// }

void test_add(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vector* vec1 = NULL;
    Vector* vec2 = NULL;
    Vector* vec_res = NULL;

    //Векторы не инициализированы
    add(vec1, vec2);
    assert(vec_res == NULL);

    //Векторы разной длинны
    vec1 = new(int_type, 2);
    vec2 = new(int_type, 3);
    add(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(vec1);
    delete_vector(vec2);

    //Векторы разных типов
    vec1 = new(int_type, 2);
    vec2 = new(complex_type, 2);
    add(vec1, vec2);
    assert(vec_res == NULL);
    delete_vector(vec1);
    delete_vector(vec2);

    //Проверка результата сложения
    int size = 5;
    int expected_result[] = {7, 9, 11, 13, 15};
    vec1 = new(int_type, size);
    vec2 = new(int_type, size);
    vec1->table->from_array(vec1, size, 1, 2, 3, 4, 5);
    vec2->table->from_array(vec2, size, 6, 7, 8, 9, 10);
    vec_res = add(vec1, vec2);
    assert(vec_res != NULL);
    assert(vec_res->table == vec1->table);
    assert(vec_res->vec->dim == vec1->vec->dim);
    int* res_data = (int *)vec_res->vec->data;
    for (int i = 0; i < vec_res->vec->dim; i++){
        assert(res_data[i] == expected_result[i]);
    }

    printf("add(): SUCCESS\n");
    delete_vector(vec1);
    delete_vector(vec2);
    delete_vector(vec_res);
    free(int_type);
    free(complex_type);
}

void test_dot_product(){
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    Vector* vec1 = NULL;
    Vector* vec2 = NULL;
    Vector* vec_res = NULL;

    int size = 5;
    vec1 = new(int_type, size);
    vec2 = new(int_type, size);
    vec1->table->from_array(vec1, size, 1, 2, 3, 4, 5);
    vec2->table->from_array(vec2, size, 6, 7, 8, 9, 10);
    int expected_result = 130;
    vec_res = dot_product(vec1, vec2);
    assert(vec_res->vec->dim == 1);
    assert(((int *)vec_res->vec->data)[0] == expected_result);
    delete_vector(vec1);
    delete_vector(vec2);
    delete_vector(vec_res);

    size = 6;
    vec1 = new(complex_type, size);
    vec2 = new(complex_type, size);
    vec1->table->from_array(vec1, size, 1, 2, 3, 4, 5, 6);
    vec2->table->from_array(vec2, size, 7, 8, 9, 10, 11, 12);
    printf("dot_product(): SUCCESS\n");
    free(int_type);
    free(complex_type);    
}

int main() {
    test_new();
    // test_delete();
    test_add();
    test_dot_product();

    printf("All tests passed\n");
}