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

#include <math.h>

// Function to compute sum of first n squares
int sum_first_n_squares(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

// Function to compute difference ratio (a - b) / (a + b)
double diff_ratio(double a, double b) {
    if ((a + b) == 0.0) return 0.0;
    return (a - b) / (a + b);
}

// Function to compute sign-preserving square
double signed_square(double x) {
    return (x >= 0) ? x * x : -x * x;
}

#include <math.h>

// Function to compute nth triangular number using loop
int triangular_loop(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

// Function to compute harmonic mean of three numbers
double harmonic_mean3(double a, double b, double c) {
    double denom = (1.0/a + 1.0/b + 1.0/c);
    if (denom == 0.0) return 0.0;
    return 3.0 / denom;
}

// Function to compute cube difference a^3 - b^3
double cube_diff(double a, double b) {
    return a*a*a - b*b*b;
}

#include <math.h>

// Function to compute sum of first n cubes using formula
int sum_cubes_formula(int n) {
    int s = n * (n + 1) / 2;
    return s * s;
}

// Function to compute normalized difference |a - b| / max(a, b)
double normalized_diff(double a, double b) {
    double m = fmax(fabs(a), fabs(b));
    if (m == 0.0) return 0.0;
    return fabs(a - b) / m;
}

// Function to compute inverse cube
double inv_cube(double x) {
    if (x == 0.0) return 0.0;
    return 1.0 / (x * x * x);
}
#include <math.h>

// Function to compute alternating product: 1 * 2 * 3 * ... * n with sign flips
int alternating_product(int n) {
    int prod = 1;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0)
            prod *= -i;
        else
            prod *= i;
    }
    return prod;
}

// Function to compute average of three numbers
double avg3(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

// Function to compute exponential scaling: a * e^(kx)
double exp_scale(double a, double k, double x) {
    return a * exp(k * x);
}

#include <math.h>

// Function to compute sum of divisors of n
int sum_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            sum += i;
    }
    return sum;
}

// Function to compute midpoint of three numbers (average)
double midpoint3(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

// Function to compute log base 2
double log_base2(double x) {
    if (x <= 0.0) return 0.0;
    return log(x) / log(2.0);
}

#include <math.h>

// Function to compute product of array elements
double product_array(double arr[], int size) {
    double product = 1.0;
    for (int i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

// Function to compute nth term of arithmetic progression
double nth_term_ap(double a, double d, int n) {
    return a + (n - 1) * d;
}

// Function to compute cube root using pow
double cube_root(double x) {
    return pow(x, 1.0 / 3.0);
}

// Function to compute midpoint between two numbers
double midpoint(double a, double b) {
    return (a + b) / 2.0;
}

// Function to compute sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

#include <math.h>

// Compute square difference
double square_diff(double a, double b) {
    double res = a*a - b*b;
    return fabs(res);
}



#include <math.h>

#define EPS 1e-9

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n % 2 == 0 && n != 2) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

long long factorial(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;

    long long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

double power(double base, int exp) {
    if (exp == 0) return 1;

    double result = 1;
    int e = exp > 0 ? exp : -exp;

    for (int i = 0; i < e; i++) {
        result *= base;
    }

    return (exp < 0) ? 1 / result : result;
}

int sumOfDigits(int n) {
    int sum = 0;
    n = (n < 0) ? -n : n;

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int isPalindrome(int n) {
    int original = n;
    int reversed = 0;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return original == reversed;
}

double squareRoot(double x) {
    if (x < 0) return -1;

    double guess = x;
    while (fabs(guess * guess - x) > EPS) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

int countDivisors(int n) {
    if (n <= 0) return 0;

    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count += (i * i == n) ? 1 : 2;
        }
    }
    return count;
}

int isPerfectSquare(int n) {
    if (n < 0) return 0;

    int root = (int)sqrt(n);
    return root * root == n;
}

int sumOfN(int n) {
    if (n < 0) return -1;
    return n * (n + 1) / 2;
}

int sumOfSquares(int n) {
    if (n < 0) return -1;
    return n * (n + 1) * (2 * n + 1) / 6;
}

double harmonicSum(int n) {
    if (n <= 0) return 0;

    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

#include <math.h>

#define EPS 1e-7

double geometricSum(double a, double r, int n) {
    if (n <= 0) return 0;

    if (fabs(r - 1.0) < EPS)
        return a * n;

    return a * (1 - pow(r, n)) / (1 - r);
}

double arithmeticSum(double a, double d, int n) {
    if (n <= 0) return 0;
    return (n / 2.0) * (2 * a + (n - 1) * d);
}

int isHarshad(int n) {
    if (n <= 0) return 0;

    int sum = 0, temp = n;
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }

    return (sum != 0 && n % sum == 0);
}

int nextPrime(int n) {
    int num = n + 1;

    while (1) {
        int prime = 1;
        if (num <= 1) prime = 0;

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                prime = 0;
                break;
            }
        }

        if (prime) return num;
        num++;
    }
}

int eulerTotient(int n) {
    if (n <= 0) return 0;

    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

double exponentialApprox(double x, int terms) {
    if (terms <= 0) return 1;

    double sum = 1.0;
    double term = 1.0;

    for (int i = 1; i < terms; i++) {
        term *= x / i;
        sum += term;
    }
    return sum;
}

double sineApprox(double x, int terms) {
    double sum = 0.0;
    int sign = 1;

    for (int i = 0; i < terms; i++) {
        int power = 2 * i + 1;
        double fact = 1;

        for (int j = 1; j <= power; j++)
            fact *= j;

        sum += sign * pow(x, power) / fact;
        sign *= -1;
    }
    return sum;
}

double cosineApprox(double x, int terms) {
    double sum = 0.0;
    int sign = 1;

    for (int i = 0; i < terms; i++) {
        int power = 2 * i;
        double fact = 1;

        for (int j = 1; j <= power; j++)
            fact *= j;

        sum += sign * pow(x, power) / fact;
        sign *= -1;
    }
    return sum;
}

int isCoPrime(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a == 1;
}

int sumOfProperDivisors(int n) {
    if (n <= 1) return 0;

    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n)
                sum += i;
            else
                sum += i + (n / i);
        }
    }
    return sum;
}

int isAbundant(int n) {
    return sumOfProperDivisors(n) > n;
}

int isDeficient(int n) {
    return sumOfProperDivisors(n) < n;
}

double logApprox(double x) {
    if (x <= 0) return -1;

    double y = (x - 1) / (x + 1);
    double y2 = y * y;
    double result = 0.0;

    for (int i = 1; i < 20; i += 2) {
        result += (1.0 / i) * pow(y, i);
    }

    return 2 * result;
}

#include <math.h>

#define EPS 1e-6
#define MAX_ITER 1000

double evaluatePolynomial(double coeffs[], int degree, double x) {
    double result = 0.0;

    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

double derivativePolynomial(double coeffs[], int degree, double x) {
    double result = 0.0;

    for (int i = 1; i <= degree; i++) {
        result += i * coeffs[i] * pow(x, i - 1);
    }
    return result;
}

double newtonRaphson(double coeffs[], int degree, double initialGuess) {
    double x = initialGuess;

    for (int i = 0; i < MAX_ITER; i++) {
        double fx = evaluatePolynomial(coeffs, degree, x);
        double dfx = derivativePolynomial(coeffs, degree, x);

        if (fabs(dfx) < EPS)
            break;

        double x1 = x - fx / dfx;

        if (fabs(x1 - x) < EPS)
            return x1;

        x = x1;
    }
    return x;
}

double bisection(double coeffs[], int degree, double low, double high) {
    double mid;

    for (int i = 0; i < MAX_ITER; i++) {
        mid = (low + high) / 2;
        double fmid = evaluatePolynomial(coeffs, degree, mid);

        if (fabs(fmid) < EPS)
            return mid;

        double flow = evaluatePolynomial(coeffs, degree, low);

        if (flow * fmid < 0)
            high = mid;
        else
            low = mid;
    }
    return mid;
}

double integrateTrapezoidal(double coeffs[], int degree, double a, double b, int n) {
    if (n <= 0) return 0;

    double h = (b - a) / n;
    double sum = 0.5 * (evaluatePolynomial(coeffs, degree, a) +
                        evaluatePolynomial(coeffs, degree, b));

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += evaluatePolynomial(coeffs, degree, x);
    }

    return sum * h;
}

double integrateSimpson(double coeffs[], int degree, double a, double b, int n) {
    if (n <= 0 || n % 2 != 0) return 0;

    double h = (b - a) / n;
    double sum = evaluatePolynomial(coeffs, degree, a) +
                 evaluatePolynomial(coeffs, degree, b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * evaluatePolynomial(coeffs, degree, x);
        else
            sum += 4 * evaluatePolynomial(coeffs, degree, x);
    }

    return sum * h / 3;
}

double mean(double arr[], int n) {
    if (n <= 0) return 0;

    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum / n;
}

double standardDeviation(double arr[], int n) {
    if (n <= 1) return 0;

    double m = mean(arr, n);
    double sum = 0;

    for (int i = 0; i < n; i++) {
        double diff = arr[i] - m;
        sum += diff * diff;
    }

    return sqrt(sum / n);
}

int linearRecurrence(int n) {
    if (n <= 1) return n;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
}

int isGeometricProgression(int arr[], int n) {
    if (n < 2) return 1;
    if (arr[0] == 0) return 0;

    double ratio = (double)arr[1] / arr[0];

    for (int i = 2; i < n; i++) {
        if (fabs((double)arr[i] / arr[i - 1] - ratio) > EPS)
            return 0;
    }
    return 1;
}

int isArithmeticProgression(int arr[], int n) {
    if (n < 2) return 1;

    int diff = arr[1] - arr[0];

    for (int i = 2; i < n; i++) {
        if (arr[i] - arr[i - 1] != diff)
            return 0;
    }
    return 1;
}

double median(double arr[], int n) {
    if (n <= 0) return 0;

    if (n % 2 == 1)
        return arr[n / 2];
    else
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;

}


int square(int x) {
    return x * x;
}

int cube(int x) {
    return x * x * x;
}

int maxOfThree(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

int minOfThree(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int isPositive(int n) {
    return n > 0;
}

int isNegative(int n) {
    return n < 0;
}

int absolute(int n) {
    return (n < 0) ? -n : n;
}

int sum(int a, int b) {
    return a + b;
}

int difference(int a, int b) {
    return a - b;
}

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int maxArray(int arr[], int size) {
    if (size <= 0) return -1;

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int minArray(int arr[], int size) {
    if (size <= 0) return -1;

    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

double averageArray(int arr[], int size) {
    if (size <= 0) return 0;

    int sum = sumArray(arr, size);
    return (double)sum / size;
}

int countEven(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0)
            count++;
    }
    return count;
}

int countOdd(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0)
            count++;
    }
    return count;
}

void reverseArray(int arr[], int size) {
    int left = 0, right = size - 1;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}

int isSorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}


int findElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int countOccurrences(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            count++;
    }
    return count;
}

void incrementArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] += value;
    }
}

void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int compareArrays(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int sumEvenIndex(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}

int sumOddIndex(int arr[], int size) {
    int sum = 0;
    for (int i = 1; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}

void rotateLeft(int arr[], int size) {
    if (size <= 1) return;

    int first = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = first;
}

void rotateRight(int arr[], int size) {
    if (size <= 1) return;

    int last = arr[size - 1];
    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}


int countGreaterThan(int arr[], int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > value)
            count++;
    }
    return count;
}

int countLessThan(int arr[], int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < value)
            count++;
    }
    return count;
}

void replaceValue(int arr[], int size, int oldVal, int newVal) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == oldVal)
            arr[i] = newVal;
    }
}

int sumPositive(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0)
            sum += arr[i];
    }
    return sum;
}

int sumNegative(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0)
            sum += arr[i];
    }
    return sum;
}

void multiplyArray(int arr[], int size, int factor) {
    for (int i = 0; i < size; i++) {
        arr[i] *= factor;
    }
}

int findFirstNegative(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0)
            return i;
    }
    return -1;
}

int findLastPositive(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] > 0)
            return i;
    }
    return -1;
}



void prefixSum(int arr[], int result[], int size) {
    if (size <= 0) return;

    result[0] = arr[0];
    for (int i = 1; i < size; i++) {
        result[i] = result[i - 1] + arr[i];
    }
}

void suffixSum(int arr[], int result[], int size) {
    if (size <= 0) return;

    result[size - 1] = arr[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        result[i] = result[i + 1] + arr[i];
    }
}

int maxDifference(int arr[], int size) {
    if (size < 2) return 0;

    int minVal = arr[0];
    int maxDiff = arr[1] - arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] - minVal > maxDiff)
            maxDiff = arr[i] - minVal;

        if (arr[i] < minVal)
            minVal = arr[i];
    }
    return maxDiff;
}

int hasDuplicates(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j])
                return 1;
        }
    }
    return 0;
}

int firstUnique(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int unique = 1;
        for (int j = 0; j < size; j++) {
            if (i != j && arr[i] == arr[j]) {
                unique = 0;
                break;
            }
        }
        if (unique) return i;
    }
    return -1;
}

void swapAdjacent(int arr[], int size) {
    for (int i = 0; i < size - 1; i += 2) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

int sumAlternate(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}


int insertAt(int arr[], int size, int capacity, int index, int value) {
    if (size >= capacity || index < 0 || index > size)
        return size;

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = value;
    return size + 1;
}

int deleteAt(int arr[], int size, int index) {
    if (size <= 0 || index < 0 || index >= size)
        return size;

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    return size - 1;
}

void shiftLeft(int arr[], int size) {
    if (size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = 0;
}

void shiftRight(int arr[], int size) {
    if (size <= 1) return;

    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = 0;
}

int findMaxIndex(int arr[], int size) {
    if (size <= 0) return -1;

    int maxIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxIdx])
            maxIdx = i;
    }
    return maxIdx;
}

int findMinIndex(int arr[], int size) {
    if (size <= 0) return -1;

    int minIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIdx])
            minIdx = i;
    }
    return minIdx;
}

int removeDuplicates(int arr[], int size) {
    if (size <= 1) return size;

    int j = 0;
    for (int i = 1; i < size; i++) {
        int duplicate = 0;
        for (int k = 0; k <= j; k++) {
            if (arr[i] == arr[k]) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

int mergeArrays(int a[], int sizeA, int b[], int sizeB, int result[]) {
    int i = 0, j = 0, k = 0;

    while (i < sizeA && j < sizeB) {
        if (a[i] < b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < sizeA)
        result[k++] = a[i++];

    while (j < sizeB)
        result[k++] = b[j++];

    return k;
}

int frequencyOfElement(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            count++;
    }
    return count;
}

int mostFrequentElement(int arr[], int size) {
    if (size <= 0) return -1;

    int maxCount = 0;
    int element = arr[0];

    for (int i = 0; i < size; i++) {
        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j])
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            element = arr[i];
        }
    }
    return element;
}

void reverseSegment(int arr[], int start, int end) {
    if (start < 0 || end < 0 || start >= end)
        return;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void bubbleSort(int arr[], int size) {
    if (size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int isSortedAscending(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

int isSortedDescending(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1])
            return 0;
    }
    return 1;
}

int partition(int arr[], int low, int high) {
    if (low < 0 || high < 0 || low >= high)
        return -1;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (pi != -1) {
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}

int countInRange(int arr[], int size, int low, int high) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= low && arr[i] <= high)
            count++;
    }
    return count;
}

int sumMatrix(int mat[][10], int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += mat[i][j];
        }
    }
    return sum;
}

void transposeMatrix(int mat[][10], int result[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }
}

int isIdentityMatrix(int mat[][10], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j && mat[i][j] != 1)
                return 0;
            if (i != j && mat[i][j] != 0)
                return 0;
        }
    }
    return 1;
}

int diagonalSum(int mat[][10], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += mat[i][i];
    }
    return sum;
}

int findMaxInMatrix(int mat[][10], int rows, int cols) {
    if (rows <= 0 || cols <= 0) return -1;

    int max = mat[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] > max)
                max = mat[i][j];
        }
    }
    return max;
}

void addMatrices(int a[][10], int b[][10], int result[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}


int setBit(int num, int pos) {
    return num | (1 << pos);
}

int clearBit(int num, int pos) {
    return num & ~(1 << pos);
}

int toggleBit(int num, int pos) {
    return num ^ (1 << pos);
}

int checkBit(int num, int pos) {
    return (num >> pos) & 1;
}

int countSetBits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int isPowerOfTwo(int num) {
    if (num <= 0) return 0;
    return (num & (num - 1)) == 0;
}

int reverseBits(int num) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;
        result |= (num & 1);
        num >>= 1;
    }
    return result;
}

int findFirstSetBit(int num) {
    if (num == 0) return -1;

    int pos = 0;
    while ((num & 1) == 0) {
        num >>= 1;
        pos++;
    }
    return pos;
}


int stringLength(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int isDigitString(const char *str) {
    if (str[0] == '\0') return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            break;
        result = result * 10 + (str[i] - '0');
    }

    return sign * result;
}

void toUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

int countWords(const char *str) {
    int count = 0;
    int inWord = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && inWord == 0) {
            inWord = 1;
            count++;
        } else if (str[i] == ' ') {
            inWord = 0;
        }
    }
    return count;
}

int compareStrings(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void reverseString(char *str) {
    int len = stringLength(str);
    int start = 0, end = len - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}




#define MAX 100

struct Stack {
    int data[MAX];
    int top;
};

void initStack(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

int push(struct Stack *s, int value) {
    if (isFull(s))
        return 0;

    s->data[++(s->top)] = value;
    return 1;
}

int pop(struct Stack *s, int *value) {
    if (isEmpty(s))
        return 0;

    *value = s->data[(s->top)--];
    return 1;
}

int peek(struct Stack *s, int *value) {
    if (isEmpty(s))
        return 0;

    *value = s->data[s->top];
    return 1;
}

int stackSize(struct Stack *s) {
    return s->top + 1;
}

void clearStack(struct Stack *s) {
    s->top = -1;
}

#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
        return NULL;

    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertAtHead(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (newNode == NULL)
        return head;

    newNode->next = head;
    return newNode;
}

struct Node* insertAtTail(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (newNode == NULL)
        return head;

    if (head == NULL)
        return newNode;

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

struct Node* deleteValue(struct Node* head, int value) {
    if (head == NULL)
        return NULL;

    struct Node* temp = head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == value) {
            if (prev == NULL) {
                struct Node* newHead = temp->next;
                free(temp);
                return newHead;
            } else {
                prev->next = temp->next;
                free(temp);
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

int searchList(struct Node* head, int value) {
    int index = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->data == value)
            return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

int listLength(struct Node* head) {
    int count = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


struct Queue {
    int data[MAX];
    int front;
    int rear;
    int size;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(struct Queue *q) {
    return q->size == 0;
}

int isQueueFull(struct Queue *q) {
    return q->size == MAX;
}

int enqueue(struct Queue *q, int value) {
    if (isQueueFull(q))
        return 0;

    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
    q->size++;
    return 1;
}

int dequeue(struct Queue *q, int *value) {
    if (isQueueEmpty(q))
        return 0;

    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return 1;
}

int peekFront(struct Queue *q, int *value) {
    if (isQueueEmpty(q))
        return 0;

    *value = q->data[q->front];
    return 1;
}

int peekRear(struct Queue *q, int *value) {
    if (isQueueEmpty(q))
        return 0;

    *value = q->data[q->rear];
    return 1;
}

int queueSize(struct Queue *q) {
    return q->size;
}

void clearQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

#include <stdlib.h>

char** createStringArray(int size) {
    if (size <= 0) return NULL;

    char** arr = (char**)malloc(sizeof(char*) * size);
    if (arr == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        arr[i] = NULL;
    }
    return arr;
}

int setString(char** arr, int index, const char* str) {
    if (arr == NULL || str == NULL || index < 0)
        return 0;

    int len = 0;
    while (str[len] != '\0') len++;

    arr[index] = (char*)malloc(len + 1);
    if (arr[index] == NULL)
        return 0;

    for (int i = 0; i < len; i++) {
        arr[index][i] = str[i];
    }
    arr[index][len] = '\0';

    return 1;
}

int getStringLength(char** arr, int index) {
    if (arr == NULL || arr[index] == NULL)
        return -1;

    int len = 0;
    while (arr[index][len] != '\0') len++;

    return len;
}

int compareStringAt(char** arr, int i, int j) {
    if (arr == NULL || arr[i] == NULL || arr[j] == NULL)
        return -2;

    int k = 0;
    while (arr[i][k] != '\0' && arr[j][k] != '\0') {
        if (arr[i][k] != arr[j][k])
            return arr[i][k] - arr[j][k];
        k++;
    }
    return arr[i][k] - arr[j][k];
}

void freeStringArray(char** arr, int size) {
    if (arr == NULL) return;

    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);
}

int countNonEmpty(char** arr, int size) {
    if (arr == NULL) return 0;

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL && arr[i][0] != '\0')
            count++;
    }
    return count;
}

#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node == NULL) return NULL;

    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* insertNode(struct TreeNode* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertNode(root->left, value);
    else
        root->right = insertNode(root->right, value);

    return root;
}

int searchNode(struct TreeNode* root, int value) {
    if (root == NULL) return 0;

    if (root->data == value)
        return 1;
    else if (value < root->data)
        return searchNode(root->left, value);
    else
        return searchNode(root->right, value);
}

int findMin(struct TreeNode* root) {
    if (root == NULL) return -1;

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

int findMax(struct TreeNode* root) {
    if (root == NULL) return -1;

    while (root->right != NULL)
        root = root->right;

    return root->data;
}

int treeHeight(struct TreeNode* root) {
    if (root == NULL) return -1;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0)
        return 0;  // simple error handling
    return a / b;
}

int maxOfThree(int a, int b, int c) {
    int max = a;

    if (b > max)
        max = b;

    if (c > max)
        max = c;

    return max;
}

int isEven(int num) {
    return (num % 2 == 0);
}

int absoluteValue(int num) {
    if (num < 0)
        return -num;
    return num;
}

int sumArray(int arr[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum;
}

int findMax(int arr[], int size) {
    if (size <= 0)
        return -1;

    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

int countEven(int arr[], int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0)
            count++;
    }

    return count;
}

int searchElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;  // return index
    }

    return -1;  // not found
}

int averageArray(int arr[], int size) {
    if (size <= 0)
        return 0;

    int sum = sumArray(arr, size);
    return sum / size;
}

int isPrime(int num) {
    if (num <= 1)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int factorial(int n) {
    if (n < 0)
        return -1;

    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0)
        return 0;

    int gcd_val = gcd(a, b);
    return (a / gcd_val) * b;
}

int sumOfDigits(int num) {
    if (num < 0)
        num = -num;

    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int reverseNumber(int num) {
    int reversed = 0;
    int sign = (num < 0) ? -1 : 1;

    if (num < 0)
        num = -num;

    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }

    return reversed * sign;
}

int isInRange(int value, int lower, int upper) {
    if (value >= lower && value <= upper)
        return 1;
    return 0;
}

int clampValue(int value, int min, int max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

int countInRange(int arr[], int size, int lower, int upper) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= lower && arr[i] <= upper)
            count++;
    }

    return count;
}

int sumInRange(int arr[], int size, int lower, int upper) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= lower && arr[i] <= upper)
            sum += arr[i];
    }

    return sum;
}

int findFirstInRange(int arr[], int size, int lower, int upper) {
    for (int i = 0; i < size; i++) {
        if (arr[i] >= lower && arr[i] <= upper)
            return i;
    }

    return -1;
}

int replaceIfOutOfRange(int arr[], int size, int lower, int upper, int replaceVal) {
    int changes = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < lower || arr[i] > upper) {
            arr[i] = replaceVal;
            changes++;
        }
    }

    return changes;
}
