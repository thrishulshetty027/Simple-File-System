/*
 *
 * Operating System Design / Diseño de Sistemas Operativos
 * (c) ARCOS.INF.UC3M.ES
 *
 * @file 	test.c
 * @brief 	Implementation of the client test routines.
 * @date	01/03/2017
 *
 */


#include <stdio.h>
#include <string.h>
#include "filesystem\\filesystem.h"
#include "test.h"


// Color definitions for asserts
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"

#define N_BLOCKS 250			// Number of blocks in the device
#define DEV_SIZE N_BLOCKS *BLOCK_SIZE // Device size, in bytes

int main()
{
	int ret = 0;
	
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST mkFS ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	printf("\nresult of run_tests_main: %d\n", ret);

	ret = run_tests_main();

	printf("\nresult of run_tests_main: %d\n", ret);

#if 0	
	/////// MKFS /////////
	ret = mkFS(DEV_SIZE);
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST mkFS ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST mkFS ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	/////// MOUNT /////////

	ret = mountFS();
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST mountFS ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST mountFS ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
 
	/////// CREATE FILE /////////

	ret = createFile("/test.txt");
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// CREATE FILE /////////
	printf("Intentamos crear un fichero con el mismo nombre, debera fallar: ");
	ret = createFile("/test.txt");
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	/////// CREATE FILE /////////
	printf("Intentamos crear un fichero con un nombre de mas de 32 caracteres, debera fallar: ");
	ret = createFile("/test.txt");
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CLOSE FILE /////////

	ret = closeFile(0); // El archivo se debe haber creado en el primer inodo libre
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// OPEN FILE /////////

	ret = openFile("/test.txt");
	int descriptor = ret;
	if (ret < 0)  
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	////// OPEN FILE /////////
	printf("Intentamos abrir un fichero que ya esta abierto, debera fallar: ");
	ret = openFile("/test.txt");
	if (ret < 0) 
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CLOSE FILE INTEGRITY /////////
	printf("Intentamos cerrar un fichero sin integridad con la función de integridad, debera fallar: ");
	ret = closeFileIntegrity(descriptor); 
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CLOSE FILE /////////

	ret = closeFile(descriptor); // El archivo se debe haber creado en el primer inodo libre
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// INCLUDE INTEGRITY /////////

	ret = includeIntegrity("/test.txt"); // El archivo  debe ser cerrado antes de hacer unmount
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST includeIntegrity ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST includeIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// CHECK INTEGRITY /////////

	ret = checkFile("/test.txt"); // El archivo  debe ser cerrado antes de hacer unmount
	if (ret == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST checkFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST checkFile ", ANSI_COLOR_RED, "CORRUPTED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST checkFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// OPEN FILE INTEGRITY /////////

	ret = openFileIntegrity("/test.txt"); // El archivo  debe ser cerrado antes de hacer unmount
	descriptor = ret;
	if (ret == -3)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "UNDEFINED ERROR\n", ANSI_COLOR_RESET);
		return -1;
	}
	if (ret == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "FILE IS CORRUPTED\n", ANSI_COLOR_RESET);
		return -1;
	}
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "FILE DOESN'T EXIST\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// CLOSE FILE /////////
	printf("Intentamos cerrar un fichero que tiene integridad con la función closeFile, debera fallar: ");
	ret = closeFile(descriptor); // El archivo se debe haber creado en el primer inodo libre
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CLOSE FILE INTEGRITY /////////

	ret = closeFileIntegrity(descriptor); 
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// OPEN FILE /////////
	printf("Intentamos abrir un fichero que tiene integridad con la función openFile, debera fallar: ");
	ret = openFile("/test.txt");
	if (ret < 0) 
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// OPEN FILE INTEGRITY /////////

	ret = openFileIntegrity("/test.txt"); // El archivo  debe ser cerrado antes de hacer unmount
	descriptor = ret;
	if (ret == -3)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "UNDEFINED ERROR\n", ANSI_COLOR_RESET);
		return -1;
	}
	if (ret == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "FILE IS CORRUPTED\n", ANSI_COLOR_RESET);
		return -1;
	}
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_RED, "FILE DOESN'T EXIST\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST openFileIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	/////// WRITE FILE /////////
		
	char buffer1 [] = {"Hola, esto es una prueba para el writeFile"};
	printf("Buffer1 vale: %li", (long int) strlen(buffer1)); //¿Va con puntero o no?
	ret = writeFile(descriptor, buffer1, strlen(buffer1));
	if (ret <= 0) // Debe ser mayor que 0 al devolvernos los bytes escritos
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST writeFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printf("Descriptor con writeFile vale: %i\n", descriptor);
	printf("Ret con writeFile vale: %i\n", ret);
	printf("El contenido del buffer1 es: %s\n", buffer1);
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST writeFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	/////// LSEEK FILE /////////

	ret = lseekFile(descriptor, 13678236, 2); // Debería llevar el puntero a la posición 0 y devolver un 0
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST lseekFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST lseekFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	printf("El retorno es: %i\n", ret);


	/////// READ FILE /////////

	char buffer2 [strlen(buffer1)];
	ret = readFile(descriptor, buffer2, strlen(buffer1));
	if (ret < 0) // 
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST readFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printf("Descriptor con readFile vale: %i\n", descriptor);
	printf("El contenido del buffer2 es: %s\n", buffer2);
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST readFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// CLOSE FILE INTEGRITY /////////

	ret = closeFileIntegrity(descriptor); 
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST closeFileIntegrity ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CREATE FILE /////////

	ret = createFile("/fichero.txt");
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/////// CREAR ENLACE SIMBOLICO ////
	ret = createLn("/fichero.txt", "enlace");
	if (ret < 0)  
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createLn ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createLn ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// CREAR ENLACE SIMBOLICO ////
	printf("Intentamos crear un enlace a un enlace, debera fallar: ");
	ret = createLn("enlace", "enlaceAenlace");
	if (ret < 0)  
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createLn ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST createLn ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}


	/////// ELIMINAR ENLACE SIMBOLICO ////
	ret = removeLn("enlace");
	if (ret < 0) // 
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeLn ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeLn ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// ELIMINAR ENLACE SIMBOLICO ////
	printf("Intentamos eliminar un enlace que no existe, debera fallar: ");
	ret = removeLn("enlaceInexistente");
	if (ret < 0) // 
	{	
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeLn ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	}else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeLn ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}

	/////// REMOVE FILE /////////

	ret = removeFile("/test.txt");
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeFile ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST removeFile ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	////// UNMOUNT /////////
	ret = unmountFS();
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST unmountFS ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST unmountFS ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	///////

#endif	// if 0
	return 0;


}




/* Initialize stack */
void initStack(Stack *s) {
    if (!s) return;
    s->top = -1;
}

/* Check if stack is empty */
int isEmpty(Stack *s) {
    return (s && s->top == -1);
}

/* Check if stack is full */
int isFull(Stack *s) {
    return (s && s->top == MAX_SIZE - 1);
}

/* Push element onto stack */
int push(Stack *s, int value) {
    if (!s || isFull(s))
        return 0;

    s->items[++(s->top)] = value;
    return 1;
}

/* Pop element from stack */
int pop(Stack *s, int *poppedValue) {
    if (!s || isEmpty(s))
        return 0;

    if (poppedValue)
        *poppedValue = s->items[(s->top)];

    s->top--;
    return 1;
}

/* Peek top element */
int peek(Stack *s, int *topValue) {
    if (!s || isEmpty(s))
        return 0;

    if (topValue)
        *topValue = s->items[s->top];

    return 1;
}


/* Iterative Binary Search */
int binary_search(int arr[], int size, int target) {
    if (!arr || size <= 0)
        return -1;

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;  // Not found
}

/* Check if array is sorted (ascending) */
/* int is_sorted(int arr[], int size) {
    if (!arr || size <= 1)
        return 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }

    return 1;
}*/

/* Safe wrapper: only search if sorted */
int safe_binary_search(int arr[], int size, int target) {
    if (!is_sorted(arr, size))
        return -1;

    return binary_search(arr, size, target);
}


/* Write text to a file */
int write_to_file(const char *filename, const char *content) {
    if (!filename || !content)
        return 0;

    FILE *fp = fopen(filename, "w");
    if (!fp)
        return 0;

    if (fputs(content, fp) == EOF) {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

/* Append text to a file */
int append_to_file(const char *filename, const char *content) {
    if (!filename || !content)
        return 0;

    FILE *fp = fopen(filename, "a");
    if (!fp)
        return 0;

    if (fputs(content, fp) == EOF) {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

/* Read entire file into dynamically allocated buffer */
char* read_from_file(const char *filename) {
    if (!filename)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp)
        return NULL;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    if (size < 0) {
        fclose(fp);
        return NULL;
    }

    char *buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, size, fp);
    buffer[read_size] = '\0';

    fclose(fp);
    return buffer;  // Caller must free()
}


/* new line of c code */ 

/* Calculate string length */
size_t my_strlen(const char *str) {
    if (!str)
        return 0;

    size_t len = 0;
    while (str[len] != '\0')
        len++;

    return len;
}

/* Copy string (destination must have enough space) */
char* my_strcpy(char *dest, const char *src) {
    if (!dest || !src)
        return NULL;

    char *ptr = dest;
    while ((*ptr++ = *src++) != '\0');

    return dest;
}

/* Compare two strings */
int my_strcmp(const char *s1, const char *s2) {
    if (!s1 || !s2)
        return -1;

    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}


#include <limits.h>

/* Check if a number is even */
int is_even(int n) {
    return !(n & 1);
}

/* Set a specific bit (0-based position) */
int set_bit(int n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(int) * CHAR_BIT))
        return -1;
    return n | (1 << pos);
}

/* Clear a specific bit */
int clear_bit(int n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(int) * CHAR_BIT))
        return -1;
    return n & ~(1 << pos);
}

/* Toggle a specific bit */
int toggle_bit(int n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(int) * CHAR_BIT))
        return -1;
    return n ^ (1 << pos);
}

/* Check if a specific bit is set */
int is_bit_set(int n, int pos) {
    if (pos < 0 || pos >= (int)(sizeof(int) * CHAR_BIT))
        return 0;
    return (n & (1 << pos)) != 0;
}



#include <stddef.h>

/* Swap two integers */
void swap(int *a, int *b) {
    if (!a || !b) return;

    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Bubble Sort (ascending order) */
void bubble_sort(int arr[], int size) {
    if (!arr || size <= 1)
        return;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* Check if array is sorted (ascending) */
int is_sorted(int arr[], int size) {
    if (!arr || size <= 1)
        return 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }

    return 1;
}


#include <stddef.h>

/* Returns the length of a string safely */
size_t safe_strlen(const char *str) {
    if (str == NULL) {
        return 0;  // Handle NULL pointer safely
    }

    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }

    return length;
}


#include <stdbool.h>

/* Returns true if n is a prime number */
bool is_prime(int n) {
    if (n <= 1)
        return false;

    if (n == 2)
        return true;

    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }

    return true;
}




/* Calculates factorial of n
   Returns -1 if input is negative or overflow occurs */
long long factorial(int n) {
    if (n < 0)
        return -1;  // Invalid input

    long long result = 1;

    for (int i = 1; i <= n; i++) {
        if (result > LLONG_MAX / i)
            return -1;  // Overflow detected

        result *= i;
    }

    return result;
}

#include <stdlib.h>

/* Appends a value to a dynamic integer array.
   Returns 0 on success, -1 on failure. */
int append_int(int **array, size_t *size, int value) {
    if (array == NULL || size == NULL)
        return -1;

    int *temp = realloc(*array, (*size + 1) * sizeof(int));
    if (temp == NULL)
        return -1;

    *array = temp;
    (*array)[*size] = value;
    (*size)++;

    return 0;
}

//new code//

#include <stdlib.h>

/* Definition of linked list node */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Inserts a new node at the beginning of the list
   Returns new head pointer, or NULL on failure */
Node* insert_front(Node *head, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;

    new_node->data = value;
    new_node->next = head;

    return new_node;
}


#include <string.h>

/* Reverses a string in place */
void reverse_string(char *str) {
    if (str == NULL)
        return;

    size_t len = strlen(str);
    if (len == 0)
        return;

    size_t start = 0;
    size_t end = len - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}



#include <stddef.h>

/* Sorts an integer array in ascending order */
void bubble_sort(int *arr, size_t size) {
    if (arr == NULL || size < 2)
        return;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

#include <stddef.h>
#include <limits.h>

/* Returns the maximum value in the array
   If array is NULL or size is 0, returns INT_MIN */
int find_max(const int *arr, size_t size) {
    if (arr == NULL || size == 0)
        return INT_MIN;

    int max = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}




#include <stdio.h>

void checkEvenOdd(int num)
{
    if (num % 2 == 0)
    {
        printf("Even\n");
    }
    else
    {
        printf("Odd\n");
    }
}


int factorial(int n)
{
    int result = 1;
    int i;

    for (i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}


void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack)
        stack->top = NULL;
    return stack;
}

int isEmpty(Stack* stack)
{
    return stack->top == NULL;
}

void push(Stack* stack, int value)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode)
        return;

    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack)
{
    if (isEmpty(stack))
        return -1;

    StackNode* temp = stack->top;
    int value = temp->data;

    stack->top = temp->next;
    free(temp);

    return value;
}

int peek(Stack* stack)
{
    if (isEmpty(stack))
        return -1;

    return stack->top->data;
}

void freeStack(Stack* stack)
{
    StackNode* current = stack->top;
    while (current)
    {
        StackNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}



#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        return NULL;

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

Node* search(Node* root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

void inorderTraversal(Node* root, void (*visit)(int))
{
    if (root == NULL)
        return;

    inorderTraversal(root->left, visit);
    visit(root->data);
    inorderTraversal(root->right, visit);
}

void freeTree(Node* root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashNode {
    char key[50];
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* table[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key)
{
    unsigned int hashValue = 0;

    while (*key)
    {
        hashValue = (hashValue * 31) + *key;
        key++;
    }

    return hashValue % TABLE_SIZE;
}

HashTable* createHashTable()
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht)
        return NULL;

    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;

    return ht;
}

void insert(HashTable* ht, const char* key, int value)
{
    unsigned int index = hash(key);

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode)
        return;

    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = ht->table[index];

    ht->table[index] = newNode;
}

int search(HashTable* ht, const char* key)
{
    unsigned int index = hash(key);
    HashNode* node = ht->table[index];

    while (node)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;

        node = node->next;
    }

    return -1;
}

void deleteKey(HashTable* ht, const char* key)
{
    unsigned int index = hash(key);
    HashNode* current = ht->table[index];
    HashNode* prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                ht->table[index] = current->next;

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void freeHashTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode* node = ht->table[i];
        while (node)
        {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(ht);
}

#include <stdlib.h>
#include <string.h>

char* rle_compress(const char* input)
{
    int len = strlen(input);
    char* output = (char*)malloc(len * 2 + 1);
    int i = 0, j = 0;

    while (i < len)
    {
        char current = input[i];
        int count = 1;

        while (i + 1 < len && input[i] == input[i + 1])
        {
            count++;
            i++;
        }

        output[j++] = current;

        if (count > 1)
        {
            char buffer[10];
            sprintf(buffer, "%d", count);
            for (int k = 0; buffer[k] != '\0'; k++)
            {
                output[j++] = buffer[k];
            }
        }

        i++;
    }

    output[j] = '\0';
    return output;
}


#include <stdlib.h>

void reverse(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateLeft(int arr[], int n, int k)
{
    if (n <= 0)
        return;

    k = k % n;

    reverse(arr, 0, k - 1);
    reverse(arr, k, n - 1);
    reverse(arr, 0, n - 1);
}

#include <stdlib.h>

int* merge_sorted_arrays(int* a, int sizeA, int* b, int sizeB)
{
    int* result = (int*)malloc((sizeA + sizeB) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < sizeA && j < sizeB)
    {
        if (a[i] < b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < sizeA)
        result[k++] = a[i++];

    while (j < sizeB)
        result[k++] = b[j++];

    return result;
}

int removeDuplicates(int arr[], int n)
{
    if (n == 0 || n == 1)
        return n;

    int j = 0;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] != arr[j])
        {
            j++;
            arr[j] = arr[i];
        }
    }

    return j + 1;
}

#include <string.h>

int longestCommonPrefix(char **strs, int count, char *result)
{
    if (count == 0)
        return 0;

    int index = 0;

    while (1)
    {
        char current = strs[0][index];

        if (current == '\0')
            break;

        for (int i = 1; i < count; i++)
        {
            if (strs[i][index] != current)
            {
                result[index] = '\0';
                return index;
            }
        }

        result[index] = current;
        index++;
    }

    result[index] = '\0';
    return index;
}


#include <string.h>

int areAnagrams(const char *str1, const char *str2)
{
    int count[256] = {0};

    while (*str1)
    {
        count[(unsigned char)*str1]++;
        str1++;
    }

    while (*str2)
    {
        count[(unsigned char)*str2]--;
        str2++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}


int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


#include <limits.h>

int findSecondLargest(int arr[], int n)
{
    if (n < 2)
        return INT_MIN;

    int largest = INT_MIN;
    int second = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > largest)
        {
            second = largest;
            largest = arr[i];
        }
        else if (arr[i] > second && arr[i] != largest)
        {
            second = arr[i];
        }
    }

    return second;
}


#include <string.h>

int isPalindrome(const char *str)
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
            return 0;

        left++;
        right--;
    }

    return 1;
}


#include <ctype.h>

int countVowels(const char *str)
{
    int count = 0;

    while (*str)
    {
        char c = tolower(*str);

        if (c == 'a' || c == 'e' || c == 'i' || 
            c == 'o' || c == 'u')
        {
            count++;
        }

        str++;
    }

    return count;
}


int binarySearch(int arr[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b == 0)
    {
        return -1; 
    }
    return a / b;
}

int is_prime(int num)
{
    if (num <= 1)
        return 0;

    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int factorial(int n)
{
    if (n < 0)
        return -1;

    int result = 1;

    for (int i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


#include <stdio.h>

/* Function to add two numbers */
int add(int a, int b)
{
    return a + b;
}

/* Function to subtract two numbers */
int subtract(int a, int b)
{
    return a - b;
}

/* Function to print a message */
void printMessage(const char *msg)
{
    printf("Message: %s\n", msg);
}

/* Function to check if a number is even */
int isEven(int num)
{
    if (num % 2 == 0)
        return 1;
    else
        return 0;
}

#include <stdio.h>

/* Function to find the maximum value in an array */
int findMax(int arr[], int size)
{
    int max = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

/* Function to calculate the sum of array elements */
int calculateSum(int arr[], int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

/* Function to print array elements */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* Function to reverse an array */
void reverseArray(int arr[], int size)
{
    int start = 0;
    int end = size - 1;

    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[50];
    float salary;
} Employee;

/* Initialize employee */
void initEmployee(Employee *emp, int id, const char *name, float salary)
{
    emp->id = id;
    strncpy(emp->name, name, sizeof(emp->name) - 1);
    emp->name[sizeof(emp->name) - 1] = '\0';
    emp->salary = salary;
}

/* Print employee details */
void printEmployee(const Employee *emp)
{
    printf("ID: %d\n", emp->id);
    printf("Name: %s\n", emp->name);
    printf("Salary: %.2f\n", emp->salary);
}

/* Update salary */
void updateSalary(Employee *emp, float newSalary)
{
    if (newSalary > 0)
    {
        emp->salary = newSalary;
    }
}

/* Compare two employees by salary */
int compareSalary(const Employee *e1, const Employee *e2)
{
    if (e1->salary > e2->salary)
        return 1;
    else if (e1->salary < e2->salary)
        return -1;
    else
        return 0;
}


#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* Create a new node */
Node* createNode(int value)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

/* Insert node at the beginning */
Node* insertAtBeginning(Node *head, int value)
{
    Node *newNode = createNode(value);
    if (newNode == NULL)
    {
        return head;
    }

    newNode->next = head;
    return newNode;
}

/* Print linked list */
void printList(Node *head)
{
    Node *temp = head;

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

/* Free the entire list */
void freeList(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

#include <stdio.h>

struct Student {
    char name[50];
    int age;
};

int main() {
    struct Student s1 = {"Alice", 20};

    printf("Name: %s\n", s1.name);
    printf("Age: %d\n", s1.age);

    return 0;
}


#include <stdio.h>

int main() {
    int n = 5;
    int a = 0, b = 1, next;

    printf("Fibonacci Series: %d %d ", a, b);

    for (int i = 2; i < n; i++) {
        next = a + b;
        printf("%d ", next);
        a = b;
        b = next;
    }

    return 0;
}

#include <stdio.h>

int main() {
    char str[] = "Hello World";
    int i, count = 0;

    for (i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U') {
            count++;
        }
    }

    printf("Number of vowels: %d\n", count);

    return 0;
}


#include <stdio.h>

int main() {
    int num = 29, i, flag = 0;

    for (i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("%d is a Prime number\n", num);
    else
        printf("%d is not a Prime number\n", num);

    return 0;
}

#include <stdio.h>

int main() {
    int num = 1234;
    int sum = 0;

    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }

    printf("Sum of digits: %d\n", sum);

    return 0;
}


#include <stdio.h>

int main() {
    int base = 2, exponent = 5;
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result = result * base;
    }

    printf("Result: %d\n", result);

    return 0;
}

#include <stdio.h>

int main() {
    int a = 24, b = 36, gcd;

    for (int i = 1; i <= a && i <= b; i++) {
        if (a % i == 0 && b % i == 0) {
            gcd = i;
        }
    }

    printf("GCD of %d and %d is %d\n", a, b, gcd);

    return 0;
}

#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    float average;

    average = (a + b + c) / 3.0;

    printf("Average: %.2f\n", average);

    return 0;
}
#include <stdio.h>

int main() {
    float radius = 5.0;
    float area;

    area = 3.14159 * radius * radius;

    printf("Area of circle: %.2f\n", area);

    return 0;
}


#include <stdio.h>

int main() {
    int num = 49;
    int i;
    int isSquare = 0;

    for (i = 1; i * i <= num; i++) {
        if (i * i == num) {
            isSquare = 1;
            break;
        }
    }

    if (isSquare)
        printf("%d is a perfect square\n", num);
    else
        printf("%d is not a perfect square\n", num);

    return 0;
}


#include <stdio.h>

int factorial(int n)
{
    int result = 1;

    for (int i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}
