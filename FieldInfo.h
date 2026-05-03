#pragma once

#include <stdio.h>
#include <stdlib.h>

struct FieldInfo {
    unsigned int item_size;
    int (*comparator)(void*, void*);
    int (*to_string)(void*, char*, size_t);
};

typedef struct FieldInfo FieldInfo;

FieldInfo* get_double_field_info();
FieldInfo* get_complex_field_info();