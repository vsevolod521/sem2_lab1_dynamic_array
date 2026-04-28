#pragma once

#include <stdio.h>
#include <stdlib.h>

struct FieldInfo {
    unsigned int item_size;
    int (*comparator)(void*, void*);
    void (*print)(void*);
};

typedef struct FieldInfo FieldInfo;

FieldInfo* get_double_field_info();
FieldInfo* get_complex_field_info();