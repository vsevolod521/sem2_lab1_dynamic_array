#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "FieldInfo.h"


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

void print_array(DynamicArray* array) {
    if (!array || !array->data) return;

    for (int i = 0; i < array->size; i++) {
        void* elem_ptr = get_element_ptr(array, i);
        if (elem_ptr) {
            array->field_info->print(elem_ptr); 
            printf(" ");
        }
    }
    printf("\n");
}

/*
void sort(DynamicArray* array) {
    for (int i = 0; i < array->size; i++) {
        int min_j = i;

        for (int j = i + 1; j < array->size; j++) {
            if (array->field_info->comparator(get_element_ptr(array, j), get_element_ptr(array, min_j) < 0)) {
                min_j = j;
            }
        

        void* p1 = get_element_ptr(array,i);
        void* p2 = get_element_ptr(array,i);

        p = get_element_ptr(array,min_j);
        array->data[min_j] = p;
    }
}
*/

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