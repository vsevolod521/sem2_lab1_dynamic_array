#pragma once

#include "FieldInfo.h"

FieldInfo* get_double_field_info();

int compare_double(void*, void*);
void print_double(void*);

void free_double_filed_info();

void* get_sqr(void*);

void* increase_10(void*);

void* change_sign(void*);

int is_positive(void*);

int is_double_digits(void*);