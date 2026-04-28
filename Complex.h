#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "FieldInfo.h"

struct Complex {
    double Re;
    double Im;
};

typedef struct Complex Complex;

FieldInfo* get_complex_field_info();

int compare_complex(void*, void*);
void print_complex(void*);

void free_complex_filed_info();

void* change_sign_complex(void*);
void* get_sqr_complex(void*);

int is_real_positive(void*);
int is_complex_in_unit_circle(void*);