#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>  
#include <assert.h> 

#include "tests.h"


#define EPSILON 1e-9

#define ASSERT_EQUAL_DOUBLE(actual, expected) \
        if (fabs((actual) - (expected)) > EPSILON) { \
            printf("ASSERTION FAILED: %g != %g (diff: %g, at line %d)\n", (actual), (expected), fabs((actual) - (expected)), __LINE__); \
            exit(EXIT_FAILURE); \
        }
    


#define ASSERT_EQUAL_INT(actual, expected) \
        if ((actual) != (expected)) { \
            printf("ASSERTION FAILED: %d != %d (at line %d)\n", (actual), (expected), __LINE__); \
            exit(EXIT_FAILURE); \
        }
    


#define ASSERT_EQUAL_COMPLEX(actual, expected) \
        if (fabs((actual).Re - (expected).Re) > EPSILON || fabs((actual).Im - (expected).Im) > EPSILON) { \
            printf("ASSERTION FAILED: Complex (%g, %g) != (%g, %g) (at line %d)\n", \
                   (actual).Re, (actual).Im, (expected).Re, (expected).Im, __LINE__); \
            exit(EXIT_FAILURE); \
        }
    


void run_tests() {
    run_tests_double();
    run_tests_complex();
}

void run_tests_double() {
    test_double_compare();
    test_double_create();
    test_double_sort();
    test_double_map();
    test_double_where();
    test_double_concatenate();
}

void test_double_compare() {
    double x1 = 1.0, x2 = 1.0, x3 = 1.0001;
    ASSERT_EQUAL_INT(compare_double(&x1, &x2), 0);
    ASSERT_EQUAL_INT(compare_double(&x1, &x3), -1);
    ASSERT_EQUAL_INT(compare_double(&x3, &x1), 1);
}

void test_double_create() {
    DynamicArray* array = create(get_double_field_info());

    ASSERT_EQUAL_INT(array->size, 0);
    ASSERT_EQUAL_INT(array->field_info == get_double_field_info(), 1);

    for (double x = -10; x <= 10; x += 0.1)
        push_back(array, &x);

    ASSERT_EQUAL_INT(array->size, 201);

    int i = 0;
    for (double x = -10; x <= 10; x += 0.1) {
        double retrieved_val = *(double*)(array->data[i]);
        ASSERT_EQUAL_DOUBLE(retrieved_val, x);
        i++;
    }

    delete_array(array);
}

void test_double_sort() {
    DynamicArray* array = create(get_double_field_info());

    double nums[10] = { 9.1, 5, 1, 6.5, 2, 3, 0.2, 4, 7.8, 8.0 };
    double sorted_nums[10] = { 0.2, 1, 2, 3, 4, 5, 6.5, 7.8, 8.0, 9.1};

    for (int i = 0; i < 10; i++)
        push_back(array, &nums[i]);

    sort(array);

    for (int i = 0; i < 10; i++) {
        double actual_val = *(double*)(array->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, sorted_nums[i]);
    }

    delete_array(array);
}

void test_double_map() {
    enum { size = 3};
    double nums[size] = { 1.2, -5.6, 12.0};
    double sqrs[size] = { 1.44, 31.36, 144.0 };
    double increased[size] = { 11.2, 4.4, 22.0 };
    double changed[size] = { -1.2, 5.6, -12.0 };

    DynamicArray* array = create(get_double_field_info());

    for (int i = 0; i < size; i++)
        push_back(array, &nums[i]);

    DynamicArray* result = map(array, get_sqr);
    ASSERT_EQUAL_INT(result->size, size);

    for (int i = 0; i < size; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, sqrs[i]); 
    }
    delete_array(result);

    result = map(array, increase_10);
    ASSERT_EQUAL_INT(result->size, size);

    for (int i = 0; i < size; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, increased[i]);
    }
    delete_array(result);

    result = map(array, change_sign);
    ASSERT_EQUAL_INT(result->size, size);

    for (int i = 0; i < size; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, changed[i]);
    }
    delete_array(result);

    delete_array(array);
}


void test_double_where() {
    enum { size = 5};
    double nums[size] = {2.5, -25.6, 100.1, 10.0, -99.0};
    double positives[3] = { 2.5, 100.1, 10.0 };
    double doubles[3] = { -25.6, 10.0, -99.0 };

    DynamicArray* array = create(get_double_field_info());

    for (int i = 0; i < size; i++)
        push_back(array, &nums[i]);

    DynamicArray* result = where(array, is_positive);
    ASSERT_EQUAL_INT(result->size, 3);

    for (int i = 0; i < 3; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, positives[i]);
    }
    delete_array(result);

    result = where(array, is_double_digits);
    ASSERT_EQUAL_INT(result->size, 3);

    for (int i = 0; i < 3; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, doubles[i]);
    }
    delete_array(result);

    delete_array(array);
}

void test_double_concatenate() {
    enum{size_a = 3};
    enum{size_b = 2};
    double a_nums[size_a] = { 1.5, -2.0, 0.0 };
    double b_nums[size_b] = { 42.1, -1.1 };

    DynamicArray* array_a = create(get_double_field_info());
    DynamicArray* array_b = create(get_double_field_info());

    for (int i = 0; i < size_a; i++) {
        push_back(array_a, &a_nums[i]);
    }

    for (int i = 0; i < size_b; i++) {
        push_back(array_b, &b_nums[i]);
    }

    DynamicArray* result = concatenate(array_a, array_b);
    ASSERT_EQUAL_INT(result != NULL, 1);
    ASSERT_EQUAL_INT(result->size, size_a + size_b);

    for (int i = 0; i < size_a; i++) {
        double actual_val = *(double*)(result->data[i]);
        ASSERT_EQUAL_DOUBLE(actual_val, a_nums[i]);
    }
    for (int i = 0; i < size_b; i++) {
        double actual_val = *(double*)(result->data[size_a + i]);
        ASSERT_EQUAL_DOUBLE(actual_val, b_nums[i]);
    }

    delete_array(result);
    delete_array(array_a);
    delete_array(array_b);

    DynamicArray* empty_a = create(get_double_field_info());
    DynamicArray* non_empty_b = create(get_double_field_info());
    double temp_val = 99.9;
    push_back(non_empty_b, &temp_val);

    DynamicArray* res_empty_a = concatenate(empty_a, non_empty_b);
    ASSERT_EQUAL_INT(res_empty_a != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_a->size, 1);
    double retrieved_temp = *(double*)(res_empty_a->data[0]);
    ASSERT_EQUAL_DOUBLE(retrieved_temp, temp_val);
    delete_array(res_empty_a);
    delete_array(empty_a);
    delete_array(non_empty_b);

    DynamicArray* non_empty_a = create(get_double_field_info());
    push_back(non_empty_a, &temp_val);
    DynamicArray* empty_b = create(get_double_field_info());

    DynamicArray* res_empty_b = concatenate(non_empty_a, empty_b);
    ASSERT_EQUAL_INT(res_empty_b != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_b->size, 1);
    retrieved_temp = *(double*)(res_empty_b->data[0]);
    ASSERT_EQUAL_DOUBLE(retrieved_temp, temp_val);
    delete_array(res_empty_b);
    delete_array(non_empty_a);
    delete_array(empty_b);

    DynamicArray* empty_c = create(get_double_field_info());
    DynamicArray* empty_d = create(get_double_field_info());

    DynamicArray* res_empty_both = concatenate(empty_c, empty_d);
    ASSERT_EQUAL_INT(res_empty_both != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_both->size, 0);
    ASSERT_EQUAL_INT(res_empty_both->field_info == get_double_field_info(), 1);
    delete_array(res_empty_both);
    delete_array(empty_c);
    delete_array(empty_d);

    DynamicArray* array_for_null_test = create(get_double_field_info());
    ASSERT_EQUAL_INT(concatenate(NULL, array_for_null_test) == NULL, 1);
    ASSERT_EQUAL_INT(concatenate(array_for_null_test, NULL) == NULL, 1);
    ASSERT_EQUAL_INT(concatenate(NULL, NULL) == NULL, 1);
    delete_array(array_for_null_test);
}

void run_tests_complex() {
    test_complex_create();
    test_complex_sort();
    test_complex_map();
    test_complex_where();
    test_complex_concatenate();
}

void test_complex_create() {
    DynamicArray* array = create(get_complex_field_info());

    ASSERT_EQUAL_INT(array->size, 0);
    ASSERT_EQUAL_INT(array->field_info == get_complex_field_info(), 1);

    Complex nums[4] = {
        {1.0, 2.0},
        {-3.5, 0.0},
        {0.0, -1.0},
        {2.2, 3.3}
    };

    for (int i = 0; i < 4; i++) {
        push_back(array, &nums[i]);
    }

    ASSERT_EQUAL_INT(array->size, 4);

    for (int i = 0; i < 4; i++) {
        Complex actual_val = *(Complex*)(array->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, nums[i]);
    }

    delete_array(array);
}

void test_complex_sort() {
    DynamicArray* array = create(get_complex_field_info());

    Complex nums[5] = {
        {3.0, 4.0},
        {0.0, 1.0},
        {1.0, 1.0},
        {-2.0, 0.0},
        {0.5, 0.5}
    };

    Complex sorted_expected[5] = {
        {0.5, 0.5},
        {0.0, 1.0},
        {1.0, 1.0},
        {-2.0, 0.0},
        {3.0, 4.0}
    };

    for (int i = 0; i < 5; i++) {
        push_back(array, &nums[i]);
    }

    sort(array);

    for (int i = 0; i < 5; i++) {
        Complex actual_val = *(Complex*)(array->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, sorted_expected[i]);
    }

    delete_array(array);
}

void test_complex_map() {
    enum { size = 3 };
    Complex nums[size] = {
        {1.0, 1.0},
        {2.0, 0.0},
        {0.0, 3.0}
    };
    Complex sqrs[size] = {
        {0.0, 2.0},
        {4.0, 0.0},
        {-9.0, 0.0}
    };
    Complex negs[size] = {
        {-1.0, -1.0},
        {-2.0, 0.0},
        {0.0, -3.0}
    };

    DynamicArray* array = create(get_complex_field_info());
    for (int i = 0; i < size; i++) {
        push_back(array, &nums[i]);
    }

    DynamicArray* result = map(array, get_sqr_complex);
    ASSERT_EQUAL_INT(result->size, size);

    for (int i = 0; i < size; i++) {
        Complex actual_val = *(Complex*)(result->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, sqrs[i]);
    }
    delete_array(result);

    result = map(array, change_sign_complex);
    ASSERT_EQUAL_INT(result->size, size);

    for (int i = 0; i < size; i++) {
        Complex actual_val = *(Complex*)(result->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, negs[i]);
    }
    delete_array(result);

    delete_array(array);
}

void test_complex_where() {
    enum{size = 5};
    Complex nums[size] = {
        {1.5, 0.5},
        {0.3, 0.4},
        {-0.7, 0.1},
        {2.0, 0.0},
        {0.0, 0.9}
    };

    Complex in_circle[3] = {
        {0.3, 0.4},
        {-0.7, 0.1},
        {0.0, 0.9}
    };

    Complex real_pos[3] = {
        {1.5, 0.5},
        {0.3, 0.4},
        {2.0, 0.0}
    };

    DynamicArray* array = create(get_complex_field_info());
    for (int i = 0; i < size; i++) {
        push_back(array, &nums[i]);
    }

    DynamicArray* result = where(array, is_complex_in_unit_circle);
    ASSERT_EQUAL_INT(result != NULL, 1);
    ASSERT_EQUAL_INT(result->size, 3);

    for (int i = 0; i < 3; i++) {
        Complex actual_val = *(Complex*)(result->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, in_circle[i]);
    }
    delete_array(result);

    result = where(array, is_real_positive);
    ASSERT_EQUAL_INT(result != NULL, 1);
    ASSERT_EQUAL_INT(result->size, 3);

    for (int i = 0; i < 3; i++) {
        Complex actual_val = *(Complex*)(result->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, real_pos[i]);
    }
    delete_array(result);

    delete_array(array);
}

void test_complex_concatenate() {
    enum{size_a = 2};
    enum{size_b = 3};
    Complex a_nums[size_a] = {
        {1.0, 2.0},
        {-3.0, 0.0}
    };
    Complex b_nums[size_b] = {
        {0.0, -1.0},
        {2.5, 3.5},
        {-1.0, -1.0}
    };

    DynamicArray* array_a = create(get_complex_field_info());
    DynamicArray* array_b = create(get_complex_field_info());

    for (int i = 0; i < size_a; i++) {
        push_back(array_a, &a_nums[i]);
    }

    for (int i = 0; i < size_b; i++) {
        push_back(array_b, &b_nums[i]);
    }

    DynamicArray* result = concatenate(array_a, array_b);

    ASSERT_EQUAL_INT(result != NULL, 1);
    ASSERT_EQUAL_INT(result->size, size_a + size_b);

    for (int i = 0; i < size_a; i++) {
        Complex actual_val = *(Complex*)(result->data[i]);
        ASSERT_EQUAL_COMPLEX(actual_val, a_nums[i]);
    }
    for (int i = 0; i < size_b; i++) {
        Complex actual_val = *(Complex*)(result->data[size_a + i]);
        ASSERT_EQUAL_COMPLEX(actual_val, b_nums[i]);
    }

    delete_array(result);
    delete_array(array_a);
    delete_array(array_b);

    DynamicArray* empty_a = create(get_complex_field_info());
    DynamicArray* non_empty_b = create(get_complex_field_info());
    Complex temp_val = {99.9, -0.1};
    push_back(non_empty_b, &temp_val);

    DynamicArray* res_empty_a = concatenate(empty_a, non_empty_b);
    ASSERT_EQUAL_INT(res_empty_a != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_a->size, 1);
    Complex retrieved_temp_complex = *(Complex*)(res_empty_a->data[0]);
    ASSERT_EQUAL_COMPLEX(retrieved_temp_complex, temp_val);
    delete_array(res_empty_a);
    delete_array(empty_a);
    delete_array(non_empty_b);

    DynamicArray* non_empty_a = create(get_complex_field_info());
    push_back(non_empty_a, &temp_val);
    DynamicArray* empty_b = create(get_complex_field_info());

    DynamicArray* res_empty_b = concatenate(non_empty_a, empty_b);
    ASSERT_EQUAL_INT(res_empty_b != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_b->size, 1);
    retrieved_temp_complex = *(Complex*)(res_empty_b->data[0]);
    ASSERT_EQUAL_COMPLEX(retrieved_temp_complex, temp_val);
    delete_array(res_empty_b);
    delete_array(non_empty_a);
    delete_array(empty_b);

    DynamicArray* empty_c = create(get_complex_field_info());
    DynamicArray* empty_d = create(get_complex_field_info());

    DynamicArray* res_empty_both = concatenate(empty_c, empty_d);
    ASSERT_EQUAL_INT(res_empty_both != NULL, 1);
    ASSERT_EQUAL_INT(res_empty_both->size, 0);
    ASSERT_EQUAL_INT(res_empty_both->field_info == get_complex_field_info(), 1);
    delete_array(res_empty_both);
    delete_array(empty_c);
    delete_array(empty_d);

    DynamicArray* array_for_null_test = create(get_complex_field_info());
    ASSERT_EQUAL_INT(concatenate(NULL, array_for_null_test) == NULL, 1);
    ASSERT_EQUAL_INT(concatenate(array_for_null_test, NULL) == NULL, 1);
    ASSERT_EQUAL_INT(concatenate(NULL, NULL) == NULL, 1);
    delete_array(array_for_null_test);
}