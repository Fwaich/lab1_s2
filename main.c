#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "int.h"
//errno.h
//try...catch
//either


int main() {

    Vector* vec1 = NULL;
    Vector* vec2 = NULL;
    Vector* vec_res = NULL;
    Vtable* int_type = create_int();
    
    
    int opt;
    while (1){
        printf("\n1.Заполнить вектор 1\n");
        printf("2.Заполнить вектор 2\n");
        printf("3.Вывестим вектор 1\n");
        printf("4.Вывестим вектор 2\n");
        printf("5.Сумма векторов\n");
        printf("6.Произведение векторов\n");
        printf("7.Результат последней операции\n");
        printf("8.Завершить программу\n");
        printf("\nВыберите опцию: ");

        if (scanf("%d", &opt) == EOF) {
            printf("\n");
            opt = 8;
        } else if (opt > 8 || opt < 1) {
            printf("Такой опции нет.\n");
            while(getchar() != '\n');
        }

        int num = 0;
        int size = 0;
        char* output = NULL;
        switch(opt){
            case 1:
                if (vec1) vec1->table->delete(vec1);
                printf("Введите количество эллементов: ");
                scanf("%d", &size);
                vec1 = int_type->new(int_type, size);
                vec1->table->fill_vector(vec1);
                break; 
            case 2:
                if (vec2) vec2->table->delete(vec2);
                printf("Введите количество эллементов: ");
                scanf("%d", &size);
                vec2 = int_type->new(int_type, size);
                vec2->table->fill_vector(vec2);
                break; 
            case 3:
                output = vec1->table->to_char(vec1);
                printf("%s\n", output);
                break;
            case 4:
                output = vec2->table->to_char(vec2);
                printf("%s\n", output);
                break;
            case 5:
                if (vec_res) vec_res->table->delete(vec_res);
                if (vec1->table != vec2->table || vec1->vec->dim != vec2->vec->dim){
                    printf("Разные типы или размеры\n");
                    break;
                }
                vec_res = vec1->table->add(vec1, vec2);
                output = vec_res->table->to_char(vec_res);
                printf("%s\n", output);
                break; 
            case 6:
                if (vec_res) vec_res->table->delete(vec_res);
                if (vec1->table != vec2->table || vec1->vec->dim != vec2->vec->dim){
                    printf("Разные типы или размеры\n");
                    break;
                }
                vec_res = vec1->table->dot_product(vec1, vec2);
                output = vec_res->table->to_char(vec_res);
                printf("%s\n", output);
                break;
            case 7:

                break;
            case 8:
                if (vec1) vec1->table->delete(vec1);
                if (vec2) vec2->table->delete(vec2);
                if (vec_res) vec_res->table->delete(vec_res);
                free(int_type);
                return 0;
        }

        free(output);
        

    }

    return 0;
}