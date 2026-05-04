#ifndef TESTS_H
#define TESTS_H

#include "DynamicArray.h"
#include "Complex.h"
#include "functions_double.h"


int test_double_compare();
int test_double_create();
int test_double_sort();
int test_double_map();
int test_double_where();
int test_double_concatenate();

int test_complex_create();
int test_complex_sort();
int test_complex_map();
int test_complex_where();
int test_complex_concatenate();


void run_tests();
void run_tests_double();
void run_tests_complex();

#endif 