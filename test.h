#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "C:\\LegacyApp\\cmocka\\include\\cmocka.h"

int run_tests_main(void);

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;


long long factorial(int n);
bool is_prime(int n);
size_t safe_strlen(const char *str);
int is_sorted(int arr[], int size);
void bubble_sort(int arr[], int size);
void swap(int *a, int *b);
int is_bit_set(int n, int pos);
int toggle_bit(int n, int pos);
int clear_bit(int n, int pos);
int set_bit(int n, int pos);
int is_even(int n);
int my_strcmp(const char *s1, const char *s2);
char* my_strcpy(char *dest, const char *src);
size_t my_strlen(const char *str);
char* read_from_file(const char *filename);
int append_to_file(const char *filename, const char *content);
int write_to_file(const char *filename, const char *content);
int safe_binary_search(int arr[], int size, int target);
int binary_search(int arr[], int size, int target);
int peek(Stack *s, int *topValue);
int pop(Stack *s, int *poppedValue);
int push(Stack *s, int value);
int isFull(Stack *s);
int isEmpty(Stack *s);
void initStack(Stack *s);
