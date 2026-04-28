#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "FieldInfo.h"


DynamicArray* create(FieldInfo* field_info) {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));

    array->capacity = 0;
    array->size = 0;
    array->field_info = field_info;
    array->data = NULL;

    return array;
}

void delete_array(DynamicArray* array) {
    if (array != NULL) {
        if (array->data != NULL) {
            for (int i = 0; i < array->size; i++)
                free(array->data[i]);

            free(array->data);
        }
        free(array);
    }
}

void push_back(DynamicArray* array, void* item) {

    if (array == NULL)
        return;

    if (array->capacity == 0) {
        array->capacity = 1;
        array->data = (void**)malloc(sizeof(void*) * array->capacity);
    }

    if (array->size == array->capacity) {
        array->capacity *= 2;
        void** old_data = array->data;
        array->data = (void**)malloc(sizeof(void*) * array->capacity);
        if (old_data != NULL) { 
            for (int i = 0; i < array->size; i++)
                array->data[i] = old_data[i];
        }

        free(old_data);
    }

    array->data[array->size] = malloc(array->field_info->item_size);

    char* destination = (char*)array->data[array->size];
    char* source = (char*)item;

    for (unsigned int i = 0; i < array->field_info->item_size; i++) {
        *destination = *source;
        destination++;
        source++;
    }

    array->size++;
}

void print_array(DynamicArray* array) {
    for (int i = 0; i < array->size; i++) {
        array->field_info->print(array->data[i]);
        printf(" ");
    }
    printf("\n");
}

void sort(DynamicArray* array) {
    for (int i = 0; i < array->size; i++) {
        int min_j = i;

        for (int j = i + 1; j < array->size; j++) {
            if (array->field_info->comparator(array->data[j], array->data[min_j]) < 0)
                min_j = j;
        }

        void* p = array->data[i];
        array->data[i] = array->data[min_j];
        array->data[min_j] = p;
    }
}

DynamicArray* map(DynamicArray* array, void* (*f)(void*)) {

    DynamicArray* result = create(array->field_info);

    for (int i = 0; i < array->size; i++)
        push_back(result, f(array->data[i]));

    return result;
}

DynamicArray* where(DynamicArray* array, int (*f)(void*)) {

    DynamicArray* result = create(array->field_info);

    for (int i = 0; i < array->size; i++)
        if (f(array->data[i]))
            push_back(result, array->data[i]);

    return result;
}

    DynamicArray* concatenate(DynamicArray* left, DynamicArray* right) {
        if (!left || !right) 
            return NULL; 
        

        if (left->field_info != right->field_info)
            return NULL;

        DynamicArray* result = create(left->field_info);

        for (int i = 0; i < left->size; i++)
            push_back(result, left->data[i]);

        for (int i = 0; i < right->size; i++)
            push_back(result, right->data[i]);

        return result;
    }