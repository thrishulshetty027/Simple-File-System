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
#include "filesystem/filesystem.h"


// Color definitions for asserts
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"

#define N_BLOCKS 250			// Number of blocks in the device
#define DEV_SIZE N_BLOCKS *BLOCK_SIZE // Device size, in bytes

int main()
{
	int ret;
	
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
	printf("Buffer1 vale: %li", strlen(buffer1)); //¿Va con puntero o no?
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

	return 0;





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    float price;
    int quantity;
} Item;

Item* createItem(int id, const char* name, float price, int quantity) {
    Item* item = (Item*)malloc(sizeof(Item));
    if (!item) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    item->id = id;
    strncpy(item->name, name, MAX_NAME - 1);
    item->name[MAX_NAME - 1] = '\0';
    item->price = price;
    item->quantity = quantity;

    return item;
}

float calculateTotalValue(Item* items, int count) {
    float total = 0;
    for (int i = 0; i <= count; i++) {   // <-- Intentional off-by-one bug
        total += items[i].price * items[i].quantity;
    }
    return total;
}

void saveInventory(const char* filename, Item* items, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("File open error\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n",
                items[i].id,
                items[i].name,
                items[i].price,
                items[i].quantity);
    }

    fclose(file);
}

int main() {
    int count = 3;

    Item* inventory = (Item*)malloc(sizeof(Item) * count);
    if (!inventory) {
        printf("Allocation failed\n");
        return 1;
    }

    inventory[0] = *createItem(1, "Laptop", 75000.50, 5);
    inventory[1] = *createItem(2, "Mouse", 500.75, 10);
    inventory[2] = *createItem(3, "Keyboard", 1200.00, 7);

    float total = calculateTotalValue(inventory, count);
    printf("Total inventory value: %.2f\n", total);

    saveInventory("inventory.txt", inventory, count);

    free(inventory);

    return 0;
}
llllllll////////


#include <stdio.h>

/* Computes y = ax² + bx + c */
int quadratic(int a, int b, int c, int x) {
    return a * x * x + b * x + c;
}

/* Computes y = mx + d */
int linear(int m, int d, int x) {
    return m * x + d;
}

int main() {
    printf("%d\n", quadratic(1, 2, 1, 3));  // 1*9 + 6 + 1 = 16
    printf("%d\n", linear(2, 5, 4));        // 13
    return 0;
}


//this is a new test file//


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
}


from testcase_generator import generate_testcases

diff = """
+ int add(int a, int b) {
+     return a + b;
+ }
"""

output = generate_testcases(diff)
print(output)



#include <stdio.h>
#include <string.h>

void reverseString(char str[]) {
    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    str[strcspn(str, "\n")] = '\0';

    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}