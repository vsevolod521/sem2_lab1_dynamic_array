#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "DynamicArray.h"
#include "Complex.h"
#include "functions_double.h"
#include <locale.h>
#include "tests.h"
#include "utilits.h"

int main() {
    run_tests();
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    int type_choice;
    while (1) { 
        printf("Выберите тип данных:\n");
        printf("1. double\n");
        printf("2. Complex\n");
        printf("Введите 1 или 2: ");
        if (scanf("%d", &type_choice) == 1 && (type_choice == 1 || type_choice == 2)) {
            break;
        } else {
            printf("Неверный ввод. введите 1 или 2.\n");
            clear_input_buffer(); 
        }
    }

    DynamicArray* array = NULL;
    if (type_choice == 1) {
        array = create(get_double_field_info());
        printf("Создан массив double.\n");
    } else { 
        array = create(get_complex_field_info());
        printf("Создан массив complex.\n");
    }

    if (!array) {
        printf("Ошибка создания массива.\n");
        return 1;
    }

    int num_elements;
    while (1) { 
        printf("Сколько элементов добавить? ");
        if (scanf("%d", &num_elements) == 1 && num_elements >= 0) {
            break; 
        } else {
            printf("Неверный ввод. Введите неотрицательное целое число.\n");
            clear_input_buffer();
        }
    }

    if (type_choice == 1) {
        printf("Введите %d элементов (double):\n", num_elements);
        for (int i = 0; i < num_elements; i++) {
            double val;
            while (1) { 
                printf("Элемент %d: ", i);
                if (scanf("%lf", &val) == 1) {
                    push_back(array, &val);
                    printf("Добавлен %.2f\n", val);
                    break; 
                } else {
                    printf("Неверный ввод. Введите число (double).\n");
                    clear_input_buffer();
                }
            }
        }
    } else { 
        printf("Введите %d элементов (Complex в формате Re Im):\n", num_elements);
        for (int i = 0; i < num_elements; i++) {
            Complex val;
            while (1) {
                printf("Элемент %d (Re Im): ", i);
                if (scanf("%lf %lf", &val.Re, &val.Im) == 2) {
                    push_back(array, &val);
                    printf("Добавлен (%.2f, %.2f)\n", val.Re, val.Im);
                    break; 
                } else {
                    printf("Неверный ввод.Введите два числа (Re Im).\n");
                    clear_input_buffer(); 
                }
            }
        }
    }

    printf("\nИсходный массив: ");
    print_array(array);

    //sort(array);
    printf("Отсортированный массив: ");
    print_array(array);

    if (type_choice == 1) {
        DynamicArray* mapped = map(array, get_sqr);
        if (mapped) {
            printf("Результат Map: ");
            print_array(mapped);
            delete_array(mapped);
        } else {
            printf("Ошибка Map\n");
        }

        DynamicArray* filtered = where(array, is_positive);
        if (filtered) {
            printf("Результат Where: ");
            print_array(filtered);
            delete_array(filtered);
        } else {
            printf("Ошибка Where\n");
        }
    } else { 
        DynamicArray* mapped = map(array, get_sqr_complex);
        if (mapped) {
            printf("Результат Map: ");
            print_array(mapped);
            delete_array(mapped);
        } else {
            printf("Ошибка Map\n");
        }

        DynamicArray* filtered = where(array, is_complex_in_unit_circle);
        if (filtered) {
            printf("Результат Where: ");
            print_array(filtered);
            delete_array(filtered);
        } else {
            printf("Ошибка Where\n");
        }
    }

    delete_array(array);
    printf("конец\n");

    return 0;
    
}