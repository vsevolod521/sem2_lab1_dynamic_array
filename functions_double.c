#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "FieldInfo.h"
#include "functions_double.h"

FieldInfo* double_field_info = NULL;

#define EPSILON 1e-9

int compare_double(void* l, void* r) {
    double* p1 = (double*)l;
    double* p2 = (double*)r;
    if (fabs(*p1 - *p2) < EPSILON)
        return 0;

    if (*p1 < *p2)
        return -1;

    return 1;
}

void print_double(void* item) {
    printf("%6.2f", *(double*)item);
}

FieldInfo* get_double_field_info() {
    if (double_field_info == NULL) {
        double_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        double_field_info->item_size = sizeof(double);
        double_field_info->comparator = compare_double;
        double_field_info->to_string = double_to_string;
    }
    return double_field_info;
}

void free_double_filed_info() {
    if (double_field_info != NULL)
        free(double_field_info);
}

void* get_sqr(void* ptr) {
    double* x = (double*)malloc(sizeof(double));

    *x = *((double*)ptr) * *((double*)ptr);
    
    return x;
}

void* increase_10(void* ptr) {
    double* x = (double*)malloc(sizeof(double));

    *x = *((double*)ptr) + 10;

    return x;
}

void* change_sign(void* ptr) {
    double* x = (double*)malloc(sizeof(double));

    *x = -(*((double*)ptr));

    return x;
}


int is_positive(void* ptr) {
    return *((double*)ptr) > 0;
}

int is_double_digits(void* ptr) {
    double x = *((double*)ptr);

    if (x < 0)
        x = -x;

    return 10.0 <= x && x <= 99;
}

int double_to_string(void* item, char* buffer, size_t size) {
    if (!item || (buffer == NULL && size != 0)) {
        return -1;
    }
    double val = *(const double*)item;
    int chars_written = snprintf(buffer, size, "%6.2f", val);
    return chars_written;
}

