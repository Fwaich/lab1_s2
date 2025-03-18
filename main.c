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
    Vtable* int_type = create_int();
    
    
    

    // return 0;
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
        switch(opt){
            case 1:
                vec1 = int_type->new(int_type, 5);
                vec1->table->fill_vector(vec1);
                break; 
            case 2:
                
                break; 
            case 3:
                char* output = NULL;
                output = vec1->table->to_char(vec1);
                printf("%s\n", output);
                break;
            case 4:
                
                break;
            case 5:
                
                break; 
            case 6:
                
                break;
            case 7:

                break;
            case 8:
                free(int_type);
                if (vec1) vec1->table->delete(vec1);
                if (output) free(output);
                return 0;
        }

    }

    return 0;
}