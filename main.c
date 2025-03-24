#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "vector.h"
#include "complex.h"
#include "int.h"
//errno.h
//try...catch
//either


int main() {

    Vector* vec1 = NULL;
    Vector* vec2 = NULL;
    Vector* vec_res = NULL;
    Vtable* int_type = create_int();
    Vtable* complex_type = create_complex();
    
    
    int opt;
    while (1){
        printf("\n1.Заполнить вектор 1\n");
        printf("2.Заполнить вектор 2\n");
        printf("3.Сумма векторов\n");
        printf("4.Произведение векторов\n");
        printf("5.Завершить программу\n");
        printf("\nВыберите опцию: ");

        if (scanf("%d", &opt) == EOF) {
            printf("\n");
            opt = 5;
        } else if (opt > 5 || opt < 1) {
            printf("Такой опции нет.\n");
            while(getchar() != '\n');
        }

        int in_opt = 0;
        int size = 0;
        char* output = NULL;
        switch(opt){
            case 1:
                delete_vector(&vec1);

                printf("1.Int\n2.Complex\n");
                printf("Выберите тип: ");
                scanf("%d", &in_opt);
                if (in_opt > 2 || in_opt < 1) {
                    printf("Такой опции нет\n");
                    break;
                }

                printf("Введите количество эллементов: ");
                scanf("%d", &size);
                
                vec1 = new((in_opt == 1) ? int_type : complex_type, size);
                fill_vector(vec1);
                break; 
            case 2:
                delete_vector(&vec2);

                printf("1.Int\n2.Complex\n");
                printf("Выберите тип: ");
                scanf("%d", &in_opt);
                if (in_opt > 2 || in_opt < 1) {
                    printf("Такой опции нет\n");
                    break;
                }

                printf("Введите количество эллементов: ");
                scanf("%d", &size);
                
                vec2 = new((in_opt == 1) ? int_type : complex_type, size);
                fill_vector(vec2);
                break; 
            case 3:
                delete_vector(&vec_res);
                vec_res = add(vec1, vec2);
                output = to_char(vec_res);
                if (output) printf("%s\n", output);
                break; 
            case 4:
                delete_vector(&vec_res);
                vec_res = dot_product(vec1, vec2);
                output = to_char(vec_res);
                if (output) printf("%s\n", output);
                break;
            case 5:
                delete_vector(&vec1);
                delete_vector(&vec2);
                delete_vector(&vec_res);
                free(int_type);
                free(complex_type);
                return 0;
        }

        free(output);

        if (errno) {
            perror("Error");
            errno = 0;
        }

    }

    return 0;
}