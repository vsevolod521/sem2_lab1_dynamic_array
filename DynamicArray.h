#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "FieldInfo.h"

struct DynamicArray {
    int capacity;
    int size;
    void** data;
    FieldInfo* field_info;
};

typedef struct DynamicArray DynamicArray;

DynamicArray* create(FieldInfo*);
void delete_array(DynamicArray*);
void push_back(DynamicArray*, void*);
void print_array(DynamicArray*);

void sort(DynamicArray* array);

DynamicArray* map(DynamicArray* array, void*(*f)(void*));

DynamicArray* where(DynamicArray* array, int (*f)(void*));

DynamicArray* concatenate(DynamicArray* left, DynamicArray* right);