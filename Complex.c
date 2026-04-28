#include <stdio.h>
#include <stdlib.h>
#include "FieldInfo.h"
#include "Complex.h"

FieldInfo* complex_field_info = NULL;

int compare_complex(void* l, void* r) {
    Complex* p1 = (Complex*)l;
    Complex* p2 = (Complex*)r;
    int mod1 = p1->Re * p1->Re + p1->Im * p1->Im;
    int mod2 = p2->Re * p2->Re + p2->Im * p2->Im;
    return (mod1 > mod2) - (mod1 < mod2);
}

void print_complex(void* item) {
    Complex* num = (Complex*)item;
    printf("(%6.2f + %6.2fi)", num->Re, num->Im);
}

FieldInfo* get_complex_field_info() {
    if (complex_field_info == NULL) {
        complex_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        complex_field_info->item_size = sizeof(Complex);
        complex_field_info->comparator = compare_complex;
        complex_field_info->print = print_complex;
    }
    return complex_field_info;
}

void free_complex_filed_info() {
    if (complex_field_info != NULL)
        free(complex_field_info);
}

void* change_sign_complex(void* p1) {
    Complex* num = (Complex*)p1;
    Complex* result = (Complex*)malloc(sizeof(Complex));
    if (result != NULL) {
        result->Re = -num->Re;
        result->Im = -num->Im;
    }
    return result;
}

void* get_sqr_complex(void* p1) {
    Complex* num = (Complex*)p1;
    Complex* result = (Complex*)malloc(sizeof(Complex));
    if (result != NULL) {
        result->Re = num->Re * num->Re - num->Im * num->Im;
        result->Im = 2 * num->Re * num->Im;
    }
    return result;
}

int is_real_positive(void* p1) {
    Complex* num = (Complex*)p1;
    return (num->Re > 0.0) ? 1 : 0;
}

int is_complex_in_unit_circle(void* p1) {
    Complex* num = (Complex*)p1;
    double mod_sq = num->Re * num->Re + num->Im * num->Im;
    return (mod_sq < 1.0) ? 1 : 0;
}