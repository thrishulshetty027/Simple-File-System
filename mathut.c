#include <stdio.h>
#include <stdlib.h>

/*
 * Adds two integers
 */
int add(int a, int b) {
    return a + b;
}

/*
 * Divides two integers
 * Returns 0 if division by zero
 */
int divide(int a, int b) {
    if (b == 0) {
        return 0;   // simple error handling
    }
    return a / b;
}

/*
 * Returns maximum element in array
 * Returns -1 if array is NULL or size <= 0
 */
int max_in_array(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int max = arr[0];

    for (int i = 1; i <= size; i++) {  // <-- Intentional off-by-one bug
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

/*
 * Allocates memory for an integer array
 * Returns NULL if allocation fails
 */
int* create_array(int size) {
    if (size <= 0) {
        return NULL;
    }

    int* arr = (int*)malloc(sizeof(int) * size);

    if (!arr) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }

    return arr;
}
