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

#include <stdio.h>

/* Addition */
double add(double a, double b) {
    return a + b;
}

/* Subtraction */
double subtract(double a, double b) {
    return a - b;
}

/* Multiplication */
double multiply(double a, double b) {
    return a * b;
}

/* Division */
double divide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}

/* Calculator operation handler */
double calculate(double a, double b, char operator) {
    switch (operator) {
        case '+':
            return add(a, b);
        case '-':
            return subtract(a, b);
        case '*':
            return multiply(a, b);
        case '/':
            return divide(a, b);
        default:
            printf("Invalid operator\n");
            return 0;
    }
}

#include <stdio.h>

/* Power function: calculates base^exp */
double power(double base, int exp) {
    double result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/* Factorial function */
int factorial(int n) {
    if (n < 0) return -1; // error case
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

/* Average of array */
double average(int arr[], int size) {
    if (size == 0) return 0;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

#include <stdio.h>

/* Matrix Addition */
void addMatrices(int r, int c, int A[r][c], int B[r][c], int result[r][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* Matrix Multiplication */
void multiplyMatrices(int r1, int c1, int c2,
                      int A[r1][c1], int B[c1][c2], int result[r1][c2]) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Print Matrix */
void printMatrix(int r, int c, int M[r][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

#include <stdio.h>

/* Bubble Sort */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* Binary Search (array must be sorted) */
int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // not found
}

/* Print Array */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#include <stdio.h>
#include <stdlib.h>

/* Node structure */
struct Node {
    int data;
    struct Node* next;
};

/* Insert at beginning */
struct Node* insertAtBeginning(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) return head;

    newNode->data = value;
    newNode->next = head;
    return newNode;
}

/* Insert at end */
struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) return head;

    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

/* Delete a node by value */
struct Node* deleteValue(struct Node* head, int value) {
    if (head == NULL) return NULL;

    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        struct Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    return head;
}

/* Print list */
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

#include <stdio.h>

#define MAX 100

/* Stack structure */
typedef struct {
    int items[MAX];
    int top;
} Stack;

/* Initialize stack */
void initStack(Stack *s) {
    s->top = -1;
}

/* Check if stack is empty */
int isEmpty(Stack *s) {
    return s->top == -1;
}

/* Check if stack is full */
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

/* Push element */
int push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return -1;
    }
    s->items[++(s->top)] = value;
    return 0;
}	

/* Pop element */
int pop(Stack *s, int *value) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    *value = s->items[(s->top)--];
    return 0;
}

/* Peek top element */
int peek(Stack *s, int *value) {
    if (isEmpty(s)) {
        return -1;
    }
    *value = s->items[s->top];
    return 0;	
}


#include <stdio.h>

/* Compute GCD using Euclidean algorithm */
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* Compute LCM using GCD */
int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / gcd(a, b);
}

/* Check if a number is prime */
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

#include <stdio.h>
#include <math.h>

/* Calculate mean */
double mean(double arr[], int n) {
    if (n == 0) return 0;

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

/* Calculate variance */
double variance(double arr[], int n) {
    if (n == 0) return 0;

    double m = mean(arr, n);
    double sum = 0;

    for (int i = 0; i < n; i++) {
        double diff = arr[i] - m;
        sum += diff * diff;
    }
    return sum / n;
}

/* Calculate standard deviation */
double standardDeviation(double arr[], int n) {
    return sqrt(variance(arr, n));
}

#include <stdio.h>

/* Evaluate polynomial using Horner's Method
   coeffs[0] = highest degree coefficient */
double evaluatePolynomial(double coeffs[], int degree, double x) {
    double result = coeffs[0];

    for (int i = 1; i <= degree; i++) {
        result = result * x + coeffs[i];
    }
    return result;
}

/* Evaluate derivative of polynomial at x */
double evaluateDerivative(double coeffs[], int degree, double x) {
    double result = 0;

    for (int i = 0; i < degree; i++) {
        result = result * x + coeffs[i] * (degree - i);
    }
    return result;
}

#include <stdio.h>

/* Example function: f(x) = x^2 */
double func(double x) {
    return x * x;
}

/* Trapezoidal Rule for numerical integration */
double trapezoidal(double a, double b, int n) {
    if (n <= 0) return 0;

    double h = (b - a) / n;
    double sum = (func(a) + func(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h);
    }

    return sum * h;
}

#include <stdio.h>
#include <math.h>

/* Solve quadratic equation: ax^2 + bx + c = 0 */
int solveQuadratic(double a, double b, double c, double *root1, double *root2) {
    if (a == 0) return -1; // not a quadratic equation

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
        return 1; // two real roots
    } 
    else if (discriminant == 0) {
        *root1 = *root2 = -b / (2 * a);
        return 0; // one real root
    } 
    else {
        *root1 = -b / (2 * a);
        *root2 = sqrt(-discriminant) / (2 * a); // imaginary part
        return 2; // complex roots
    }
}


int factorial(int n) {
    if (n < 0)
        return -1; // error case
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}												