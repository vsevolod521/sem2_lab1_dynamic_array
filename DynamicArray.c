#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "FieldInfo.h"
#include <string.h>

DynamicArray* create(FieldInfo* field_info) {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));

    array->size = 0;
    array->field_info = field_info;
    array->data = NULL;

    return array;
}

void* get_element_ptr(DynamicArray* array, int index) {
    if (!array || index < 0 || index >= array->size) return NULL;
    return (char*)array->data + index * array->field_info->item_size;
}

void delete_array(DynamicArray* array) {
    if (array) {
        free(array->data);
        free(array);      
    }
}

void push_back(DynamicArray* array, void* item) {
    if (!array || !item) return;

    int new_size = array->size + 1;
    size_t new_data_size = (size_t)new_size * array->field_info->item_size;

    void* new_data = realloc(array->data, new_data_size);
    if (!new_data) {
        return;
    }

    array->data = new_data;
    array->size = new_size;

    void* dest_ptr = get_element_ptr(array, array->size - 1);
    if (dest_ptr) { 
        char* source = (char*)item;
        char* destination = (char*)dest_ptr;
        for (unsigned int i = 0; i < array->field_info->item_size; i++) {
            destination[i] = source[i];
        }
    }
}



DynamicArray* map(DynamicArray* array, void* (*f)(void*)) {
    if (!array || !f) return NULL;

    DynamicArray* result = create(array->field_info);
    if (!result) return NULL;

    for (int i = 0; i < array->size; i++) {
        void* elem_ptr = get_element_ptr(array, i);
        if (elem_ptr) {
            void* mapped_item = f(elem_ptr); 
            if (mapped_item) {
                push_back(result, mapped_item);
                free(mapped_item); 
            }
        }
    }

    return result;
}

DynamicArray* where(DynamicArray* array, int (*f)(void*)) {
    if (!array || !f) return NULL;

    DynamicArray* result = create(array->field_info);
    if (!result) return NULL;

    for (int i = 0; i < array->size; i++) {
        void* elem_ptr = get_element_ptr(array, i);
        if (elem_ptr && f(elem_ptr)) { 
            push_back(result, elem_ptr); 
        }
    }

    return result;
}

DynamicArray* concatenate(DynamicArray* left, DynamicArray* right) {
    if (!left || !right) return NULL;

    if (left->field_info != right->field_info) return NULL;

    DynamicArray* result = create(left->field_info);
    if (!result) return NULL;


    for (int i = 0; i < left->size; i++) {
        void* elem_ptr = get_element_ptr(left, i);
        if (elem_ptr) {
            push_back(result, elem_ptr);
        }
    }


    for (int i = 0; i < right->size; i++) {
        void* elem_ptr = get_element_ptr(right, i);
        if (elem_ptr) {
            push_back(result, elem_ptr);
        }
    }

    return result;
}



void print_array(DynamicArray* array) {
    if (!array || !array->data) return;

    for (int i = 0; i < array->size; i++) {
        void* elem_ptr = get_element_ptr(array, i);
        if (elem_ptr) {
            int required_len = array->field_info->to_string(elem_ptr, NULL, 0);

            if (required_len < 0) {
                printf("ошибка форматирования элемента ");
                continue;
            }

            char* buffer = malloc((required_len + 1) * sizeof(char));
            if (!buffer) {
                fprintf(stderr, "ошибка выделения памяти для вывода элемента %d.\n", i);
                printf("ошибка выделения памяти ");
                continue;
            }

            int final_len = array->field_info->to_string(elem_ptr, buffer, required_len + 1);

            if (final_len >= 0 && final_len <= required_len) {
                printf("%s ", buffer);
            } else {
                printf("ошибка заполнения буфера ");
            }

            free(buffer);
        } else {
             printf("ошибка доступа к элементу по индексу");
        }
    }
    printf("\n");
}

void swap_elements(void* elem1, void* elem2, unsigned int item_size) {
    if (!elem1 || !elem2 || item_size == 0) return;
    char temp[item_size];
    memcpy(temp, elem1, item_size);
    memcpy(elem1, elem2, item_size);
    memcpy(elem2, temp, item_size);
}


void sort(DynamicArray* array) {
    if (!array || !array->data || array->size <= 1) return;

    int n = array->size;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            void* current = get_element_ptr(array, j);
            void* next = get_element_ptr(array, j + 1);

            if (current && next && array->field_info->comparator(current, next) > 0) {
                swap_elements(current, next, array->field_info->item_size);
            }
        }
    }
}
