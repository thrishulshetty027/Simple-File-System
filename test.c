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


double power(double base, int exp) {
    double result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

double squareRoot(double num) {
    double x = num;
    double y = 1;
    double e = 0.000001; // precision

    while (x - y > e) {
        x = (x + y) / 2;
        y = num / x;
    }
    return x;
}

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}		

int stringLength(const char *str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}


#include <math.h>

// Function to calculate factorial (recursive)
int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

// Function to calculate power (x^y)
double power(double x, int y) {
    double result = 1.0;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

// Function to calculate GCD using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute sine using math library
double compute_sine(double angle) {
    return sin(angle);
}


#include <math.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1)
        return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Function to calculate nth Fibonacci number (iterative)
int fibonacci(int n) {
    if (n <= 1)
        return n;

    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// Function to compute logarithm base 10
double log_base10(double x) {
    return log10(x);
}

// Function to calculate absolute difference
double abs_diff(double a, double b) {
    return fabs(a - b);
}

#include <math.h>

// Function to compute average of an array
double compute_average(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (size > 0) ? (sum / size) : 0.0;
}

// Function to find maximum value in an array
double find_max(double arr[], int size) {
    if (size <= 0) return 0.0;

    double max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// Function to compute exponential (e^x)
double compute_exp(double x) {
    return exp(x);
}

// Function to calculate distance between two points
double distance_2d(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}


#include <math.h>

// Function to compute sum of squares up to n
int sum_of_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i;
    }
    return sum;
}

// Function to compute cube of a number
double cube(double x) {
    return x * x * x;
}

// Function to normalize a value between min and max
double normalize(double value, double min, double max) {
    if (max - min == 0)
        return 0.0;
    return (value - min) / (max - min);
}

// Function to calculate hypotenuse using Pythagoras
double hypotenuse(double a, double b) {
    return sqrt(a * a + b * b);
}

#include <math.h>

// Function to compute harmonic sum up to n
double harmonic_sum(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

// Function to compute square root using Newton-Raphson method
double sqrt_newton(double x) {
    if (x < 0) return -1; // error for negative input

    double guess = x / 2.0;
    for (int i = 0; i < 10; i++) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

// Function to compute cosine using math library
double compute_cosine(double angle) {
    return cos(angle);
}

// Function to calculate LCM using GCD
int gcd_internal(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd_internal(a, b)) * b;
}


#include <math.h>

// Function to compute geometric series sum
double geometric_sum(double a, double r, int n) {
    if (r == 1.0)
        return a * n;
    return a * (1 - pow(r, n)) / (1 - r);
}

// Function to compute variance of an array
double variance(double arr[], int size) {
    if (size <= 0) return 0.0;

    double mean = 0.0, var = 0.0;

    for (int i = 0; i < size; i++)
        mean += arr[i];
    mean /= size;

    for (int i = 0; i < size; i++)
        var += (arr[i] - mean) * (arr[i] - mean);

    return var / size;
}

// Function to clamp a value within a range
double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Function to convert degrees to radians
double deg_to_rad(double degrees) {
    return degrees * (M_PI / 180.0);
}

#include <math.h>

// Function to compute triangular number
int triangular_number(int n) {
    return (n * (n + 1)) / 2;
}

// Function to compute mean of two numbers
double mean(double a, double b) {
    return (a + b) / 2.0;
}

// Function to compute standard deviation (simple version)
double stddev(double a, double b) {
    double m = mean(a, b);
    return sqrt(((a - m) * (a - m) + (b - m) * (b - m)) / 2.0);
}

// Function to compute inverse (1/x)
double inverse(double x) {
    if (x == 0.0) return 0.0; // avoid division by zero
    return 1.0 / x;
}

// Function to compute tangent using math library
double compute_tangent(double angle) {
    return tan(angle);
}


#include <math.h>

// Function to compute sum of cubes up to n
int sum_of_cubes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i * i;
    }
    return sum;
}

// Function to compute sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Function to compute distance in 3D space
double distance_3d(double x1, double y1, double z1,
                   double x2, double y2, double z2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// Function to compute median of three numbers
double median3(double a, double b, double c) {
    if ((a >= b && a <= c) || (a >= c && a <= b)) return a;
    if ((b >= a && b <= c) || (b >= c && b <= a)) return b;
    return c;
}

#include <math.h>

// Function to compute alternating sum: 1 - 2 + 3 - 4 + ... ± n
int alternating_sum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0)
            sum -= i;
        else
            sum += i;
    }
    return sum;
}

// Function to compute nth term of arithmetic progression
double arithmetic_nth(double a, double d, int n) {
    return a + (n - 1) * d;
}

// Function to compute area of a circle
double circle_area(double radius) {
    return M_PI * radius * radius;
}

// Function to compute natural logarithm safely
double safe_log(double x) {
    if (x <= 0.0) return 0.0; // avoid domain error
    return log(x);
}

// Function to compute max of two values
double max_val(double a, double b) {
    return (a > b) ? a : b;
}

#include <math.h>

// Function to compute sum of first n natural numbers
int sum_n(int n) {
    return n * (n + 1) / 2;
}

// Function to compute product of array elements
double product_array(double arr[], int size) {
    double prod = 1.0;
    for (int i = 0; i < size; i++) {
        prod *= arr[i];
    }
    return prod;
}

// Function to compute hyperbolic sine
double compute_sinh(double x) {
    return sinh(x);
}

// Function to compute angle between two slopes
double angle_between_slopes(double m1, double m2) {
    double tan_theta = fabs((m2 - m1) / (1 + m1 * m2));
    return atan(tan_theta);
}

// Function to compute cube root
double cube_root(double x) {
    return cbrt(x);
}

#include <math.h>

// Function to compute sum of even numbers up to n
int sum_even(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    return sum;
}

// Function to compute quadratic expression ax^2 + bx + c
double quadratic(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

// Function to compute RMS (root mean square) of two numbers
double rms(double a, double b) {
    return sqrt((a * a + b * b) / 2.0);
}

// Function to compute fractional part of a number
double fractional_part(double x) {
    return x - floor(x);
}

// Function to compute minimum of three numbers
double min3(double a, double b, double c) {
    double min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

#include <math.h>

// Function to compute sum of odd numbers up to n
int sum_odd(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
    }
    return sum;
}

// Function to compute weighted average of two values
double weighted_avg(double a, double b, double w1, double w2) {
    if (w1 + w2 == 0.0) return 0.0;
    return (a * w1 + b * w2) / (w1 + w2);
}

// Function to compute secant (1/cos)
double compute_secant(double angle) {
    double c = cos(angle);
    if (c == 0.0) return 0.0; // avoid division by zero
    return 1.0 / c;
}

// Function to compute linear interpolation
double lerp(double a, double b, double t) {
    return a + t * (b - a);
}

// Function to compute sign of a number
int sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

#include <math.h>

// Function to compute sum of digits of an integer
int sum_digits(int n) {
    int sum = 0;
    n = (n < 0) ? -n : n; // handle negative numbers
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Function to compute exponential moving average (single step)
double ema(double prev_ema, double value, double alpha) {
    return alpha * value + (1.0 - alpha) * prev_ema;
}

// Function to compute cotangent (1/tan)
double compute_cot(double angle) {
    double t = tan(angle);
    if (t == 0.0) return 0.0; // avoid division by zero
    return 1.0 / t;
}

// Function to compute squared distance (no sqrt)
double squared_distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return dx * dx + dy * dy;
}

// Function to compute modulo for doubles
double mod_double(double a, double b) {
    if (b == 0.0) return 0.0;
    return fmod(a, b);
}

#include <math.h>

// Function to count number of digits in an integer
int count_digits(int n) {
    int count = 0;
    n = (n == 0) ? 1 : (n < 0 ? -n : n);
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

// Function to compute nth root using pow
double nth_root(double x, int n) {
    if (n == 0) return 0.0;
    return pow(x, 1.0 / n);
}

// Function to compute softplus function: ln(1 + e^x)
double softplus(double x) {
    return log(1.0 + exp(x));
}

// Function to compute midpoint between two values
double midpoint(double a, double b) {
    return (a + b) / 2.0;
}

// Function to wrap value within range [0, max)
double wrap(double value, double max) {
    if (max == 0.0) return 0.0;
    double result = fmod(value, max);
    return (result < 0) ? result + max : result;
}

#include <math.h>

// Sum of multiples of k up to n
int sum_multiples(int n, int k) {
    int sum = 0;
    for (int i = k; i <= n; i += k)
        sum += i;
    return sum;
}

// Compute square
double square(double x) {
    return x * x;
}

// Compute log base e of (1 + x)
double log1p_safe(double x) {
    return log1p(x);
}

#include <math.h>

// Reverse digits of a number
int reverse_number(int n) {
    int rev = 0;
    while (n != 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return rev;
}

// Compute cosine hyperbolic
double compute_cosh(double x) {
    return cosh(x);
}

// Difference of squares
double diff_squares(double a, double b) {
    return a*a - b*b;
}				

#include <math.h>

// Check if number is even
int is_even(int n) {
    return (n % 2 == 0);
}

// Compute cube sum of array
double cube_sum(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++)
        sum += arr[i]*arr[i]*arr[i];
    return sum;
}

// Compute arcsine
double compute_asin(double x) {
    return asin(x);
}

#include <math.h>

// Sum of factorial series up to n
double factorial_series(int n) {
    double sum = 0.0, fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        sum += fact;
    }
    return sum;
}

// Compute inverse square
double inv_square(double x) {
    if (x == 0.0) return 0.0;
    return 1.0 / (x * x);
}

// Compute atan
double compute_atan(double x) {
    return atan(x);
}

#include <math.h>

// Find minimum in array
double array_min(double arr[], int size) {
    if (size <= 0) return 0.0;
    double min = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

// Compute exponential decay
double exp_decay(double x, double lambda) {
    return exp(-lambda * x);
}

// Compute ceiling
double compute_ceil(double x) {
    return ceil(x);
}

#include <math.h>

// Function to compute digital root
int digital_root(int n) {
    n = (n < 0) ? -n : n;
    while (n >= 10) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    }
    return n;
}

// Function to compute harmonic mean of two numbers
double harmonic_mean(double a, double b) {
    if (a + b == 0.0) return 0.0;
    return (2.0 * a * b) / (a + b);
}

// Function to compute sec^2(x)
double sec_squared(double angle) {
    double c = cos(angle);
    if (c == 0.0) return 0.0;
    return 1.0 / (c * c);
}

// Function to compute linear decay
double linear_decay(double start, double rate, int steps) {
    double value = start;
    for (int i = 0; i < steps; i++) {
        value -= rate;
    }
    return value;
}

// Function to compute fractional power
double fractional_power(double x, double p) {
    return pow(x, p);
}

#include <math.h>

// Function to compute sum of an arithmetic progression
double arithmetic_sum(double a, double d, int n) {
    return (n / 2.0) * (2 * a + (n - 1) * d);
}

// Function to compute standard deviation
double standard_deviation(double arr[], int size) {
    if (size <= 0) return 0.0;

    double mean = 0.0, sum_sq = 0.0;

    for (int i = 0; i < size; i++)
        mean += arr[i];
    mean /= size;

    for (int i = 0; i < size; i++)
        sum_sq += (arr[i] - mean) * (arr[i] - mean);

    return sqrt(sum_sq / size);
}

// Function to compute nth triangular number
int triangular_number(int n) {
    return (n * (n + 1)) / 2;
}

// Function to compute inverse (1/x)
double inverse(double x) {
    if (x == 0.0) return 0.0; // simple guard
    return 1.0 / x;
}

#include <math.h>

// Function to compute sum of first n odd numbers
int sum_first_n_odds(int n) {
    return n * n;
}

// Function to compute square difference |a^2 - b^2|
double square_diff(double a, double b) {
    return fabs(a*a - b*b);
}

// Function to compute reciprocal square root
double inv_sqrt(double x) {
    if (x <= 0.0) return 0.0;
    return 1.0 / sqrt(x);
}

#include <math.h>

// Function to compute sum of first n even numbers
int sum_first_n_evens(int n) {
    return n * (n + 1);
}

// Function to compute absolute ratio |a/b|
double abs_ratio(double a, double b) {
    if (b == 0.0) return 0.0;
    return fabs(a / b);
}

// Function to compute natural exponent minus 1 (e^x - 1)
double exp_minus_one(double x) {
    return exp(x) - 1.0;
}