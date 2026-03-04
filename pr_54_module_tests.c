

/*
 * Module: factorial
 * Purpose: Calculate factorial of n with overflow protection
 * Example: Module-Level Tests (MT) using cmocka
 *
 * Note:
 * - Separate test file (e.g., test_factorial.c)
 * - Assumes factorial.h and factorial.c exist
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "C:\\Users\\uik03287\\Simple-File-System\\test.h"

/* ---------- Test Cases ---------- */

static void test_factorial_zero(void **state)
{
    (void) state;
    long long result = factorial(0);
    assert_int_equal(1, result);
}

static void test_factorial_positive_valid(void **state)
{
    (void) state;
    assert_int_equal(1, factorial(1));
    assert_int_equal(2, factorial(2));
    assert_int_equal(6, factorial(3));
    assert_int_equal(24, factorial(4));
    assert_int_equal(120, factorial(5));
}

static void test_factorial_large_valid(void **state)
{
    (void) state;
    assert_int_equal(720, factorial(6));
    assert_int_equal(5040, factorial(7));
    assert_int_equal(40320, factorial(8));
    assert_int_equal(362880, factorial(9));
    assert_int_equal(3628800, factorial(10));
}

static void test_factorial_negative_input(void **state)
{
    (void) state;
    assert_int_equal(-1, factorial(-1));
    assert_int_equal(-1, factorial(-5));
    assert_int_equal(-1, factorial(-100));
}

static void test_factorial_boundary_values(void **state)
{
    (void) state;
    assert_int_equal(1, factorial(INT_MAX - 1));
    assert_int_equal(1, factorial(INT_MAX));
}

static void test_factorial_overflow_detection(void **state)
{
    (void) state;
    int overflow_n = 20;
    long long result = factorial(overflow_n);
    assert_int_equal(-1, result);
}

/* ---------- Test Runner ---------- */

int run_tests_main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_factorial_zero),
        cmocka_unit_test(test_factorial_positive_valid),
        cmocka_unit_test(test_factorial_large_valid),
        cmocka_unit_test(test_factorial_negative_input),
        cmocka_unit_test(test_factorial_boundary_values),
        cmocka_unit_test(test_factorial_overflow_detection),
    };

    printf("\nRunning factorial module tests...\n");

    return cmocka_run_group_tests(tests, NULL, NULL);
}
