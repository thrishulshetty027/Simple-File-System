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




#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

int main() {
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Dynamically allocate memory
    Student *students = (Student *)malloc(n * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input data
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Marks: ");
        scanf("%f", &students[i].marks);
    }

    // Display data
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks);
    }

    // Free allocated memory
    free(students);

    return 0;
}


/new c code snippet /

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

void* producer(void* arg) {
    for (int i = 1; i <= ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[count++] = i;
        printf("Produced: %d\n", i);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
/this should generate a pr diff/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        sleep(1);  // Wait for parent to write
        printf("Child read from shared memory: %s\n", shared_memory);

        shmdt(shared_memory);
    } else {
        // Parent process
        strcpy(shared_memory, "Hello from Parent via Shared Memory!");
        printf("Parent wrote to shared memory.\n");

        wait(NULL);

        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory
    }

    return 0;
}



#include <stdio.h>

int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    int num = 5;
    printf("Factorial of %d is %d\n", num, factorial(num));
    return 0;
}


#include <stdio.h>

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num % 2 == 0)
        printf("%d is Even\n", num);
    else
        printf("%d is Odd\n", num);

    return 0;
}



#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int length, i;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    length = strlen(str);

    printf("Reversed string: ");
    for (i = length - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }

    return 0;
}



#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;

    printf("Before swap: x = %d, y = %d\n", x, y);

    swap(&x, &y);

    printf("After swap: x = %d, y = %d\n", x, y);

    return 0;
}
////



#include <stdio.h>

int main() {
    FILE *fp;
    char text[100];

    // Write to file
    fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "Hello, this is a file example in C.\n");
    fclose(fp);

    // Read from file
    fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (fgets(text, sizeof(text), fp) != NULL) {
        printf("%s", text);
    }

    fclose(fp);

    return 0;
}



#include <stdio.h>

int main() {
    int num, original, reversed = 0, remainder;

    printf("Enter an integer: ");
    scanf("%d", &num);

    original = num;

    while (num != 0) {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }

    if (original == reversed)
        printf("%d is a palindrome.\n", original);
    else
        printf("%d is not a palindrome.\n", original);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================
   MODULE FUNCTIONS
   ========================= */

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

/* =========================
   TEST ENGINE
   ========================= */

typedef int (*operation_func)(int, int);

typedef struct {
    const char *name;
    operation_func func;
} Operation;

void run_tests(Operation op, int test_count) {
    int passed = 0;

    for (int i = 0; i < test_count; i++) {
        int a = rand() % 100;
        int b = rand() % 100;

        int expected;

        // Reference logic
        if (op.func == add)
            expected = a + b;
        else if (op.func == subtract)
            expected = a - b;
        else
            expected = a * b;

        int result = op.func(a, b);

        if (result == expected) {
            passed++;
        } else {
            printf("FAIL [%s] | %d, %d | Expected: %d | Got: %d\n",
                   op.name, a, b, expected, result);
        }
    }

    printf("Operation: %s | Passed: %d/%d\n",
           op.name, passed, test_count);
}

/* =========================
   MAIN
   ========================= */

int main() {
    srand(time(NULL));

    Operation operations[] = {
        {"Addition", add},
        {"Subtraction", subtract},
        {"Multiplication", multiply}
    };

    int total_operations = sizeof(operations) / sizeof(operations[0]);

    for (int i = 0; i < total_operations; i++) {
        run_tests(operations[i], 500);
    }

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/* ============================================================
   MODULE: calc_utils
   Purpose: Mathematical utilities with safety checks
   ============================================================ */

/* Basic arithmetic */
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
    if (b == 0) return -1;
    return a / b;
}

/* Safe addition with overflow detection */
int safe_add(int a, int b) {
    if ((b > 0 && a > INT_MAX - b) ||
        (b < 0 && a < INT_MIN - b)) {
        return -1;  // overflow
    }
    return a + b;
}

/* Safe division */
int safe_divide(int a, int b) {
    if (b == 0) return -1;
    return a / b;
}

/* Even check */
int is_even(int n) {
    return (n % 2 == 0);
}

/* Factorial with validation */
int factorial(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;

    int result = 1;
    for (int i = 1; i <= n; i++) {
        if (result > INT_MAX / i) return -1;  // overflow
        result *= i;
    }
    return result;
}

/* Power function */
int power(int base, int exp) {
    if (exp < 0) return -1;

    int result = 1;
    for (int i = 0; i < exp; i++) {
        if (result > INT_MAX / base) return -1;
        result *= base;
    }
    return result;
}

/* Find maximum in array */
int find_max(int *arr, int size) {
    if (!arr || size <= 0) return -1;

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

/* Average of array */
double average(int *arr, int size) {
    if (!arr || size <= 0) return 0.0;

    long sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];

    return (double)sum / size;
}

/* Safe string copy */
int safe_copy(char *dest, int dest_size, const char *src) {
    if (!dest || !src || dest_size <= 0)
        return -1;

    int len = strlen(src);
    int copy_len = (len < dest_size) ? len : dest_size;

    strncpy(dest, src, copy_len);

    if (copy_len < dest_size)
        dest[copy_len] = '\0';

    return copy_len;
}

/* Dynamic array creation */
int* create_array(int size) {
    if (size <= 0) return NULL;

    int *arr = (int*)malloc(size * sizeof(int));
    if (!arr) return NULL;

    for (int i = 0; i < size; i++)
        arr[i] = 0;

    return arr;
}

/* ============================================================
   MODULE: linear_algebra
   Purpose: Equation solvers
   ============================================================ */

/* Solve quadratic: ax^2 + bx + c = 0
   Returns:
   0 = no real roots
   1 = one root
   2 = two real roots
*/
int solve_quadratic(double a, double b, double c,
                    double *r1, double *r2) {

    if (!r1 || !r2) return -1;

    if (a == 0) return -1;  // Not quadratic

    double discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return 0;

    if (discriminant == 0) {
        *r1 = -b / (2*a);
        return 1;
    }

    double sqrt_d = sqrt(discriminant);

    *r1 = (-b + sqrt_d) / (2*a);
    *r2 = (-b - sqrt_d) / (2*a);

    return 2;
}

/* Linear function: f(x) = mx + d */
double linear(double m, double d, double x) {
    return m*x + d;
}

/* Quadratic function evaluation */
double quadratic(double a, double b, double c, double x) {
    return a*x*x + b*x + c;
}

/* ============================================================
   MAIN (Demo Execution)
   ============================================================ */

int main() {

    printf("Add: %d\n", add(10, 5));
    printf("Safe Add (overflow test): %d\n", safe_add(INT_MAX, 1));
    printf("Factorial 5: %d\n", factorial(5));
    printf("Power 2^3: %d\n", power(2, 3));

    int arr[] = {1, 5, 3, 9, 2};
    printf("Max: %d\n", find_max(arr, 5));
    printf("Average: %.2f\n", average(arr, 5));

    char buffer[10];
    safe_copy(buffer, 10, "hello");
    printf("Copied string: %s\n", buffer);

    double r1, r2;
    int roots = solve_quadratic(1, -5, 6, &r1, &r2);
    printf("Quadratic roots count: %d\n", roots);
    if (roots > 0) printf("Root1: %.2f\n", r1);
    if (roots > 1) printf("Root2: %.2f\n", r2);

    int *dyn = create_array(5);
    if (dyn) {
        printf("Dynamic array created.\n");
        free(dyn);
    }

    return 0;
}


#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, length;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    length = strlen(str);

    // Remove newline if present
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
        length--;
    }

    // Reverse the string
    for (i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }

    printf("Reversed string: %s\n", str);

    return 0;
}


#include <stdio.h>

int isPrime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isPrime(num))
        printf("%d is a prime number.\n", num);
    else
        printf("%d is not a prime number.\n", num);

    return 0;
}

#include <stdio.h>

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    int num = 5;

    printf("Factorial of %d is %d\n", num, factorial(num));

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int countWords(FILE *file) {
    int count = 0;
    int inWord = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
    }
    return count;
}

int main() {
    FILE *file = fopen("sample.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int words = countWords(file);
    printf("Total words: %d\n", words);

    fclose(file);
    return EXIT_SUCCESS;
}



#include <stdio.h>
#include <math.h>

int main() {
    int number, originalNumber, remainder, n = 0;
    double result = 0.0;

    printf("Enter an integer: ");
    scanf("%d", &number);

    originalNumber = number;

    // Count number of digits
    while (originalNumber != 0) {
        originalNumber /= 10;
        ++n;
    }

    originalNumber = number;

    // Calculate sum of powers
    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    if ((int)result == number)
        printf("%d is an Armstrong number.\n", number);
    else
        printf("%d is not an Armstrong number.\n", number);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

int main() {
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Dynamic memory allocation
    Student *students = (Student *)malloc(n * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input student data
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Marks: ");
        scanf("%f", &students[i].marks);
    }

    // Display student data
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks);
    }

    free(students);  // Free allocated memory
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert at beginning
struct Node* insert(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// Display list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free memory
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    head = insert(head, 30);
    head = insert(head, 20);
    head = insert(head, 10);

    printf("Linked List:\n");
    display(head);

    freeList(head);
    return 0;
}


#include <stdio.h>

/* Function to calculate factorial recursively */
unsigned long long factorial(int n) {
    if (n < 0)
        return 0;  // Invalid input
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

/* Function to check if a number is prime */
int isPrime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

/* Function to swap two integers using pointers */
void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;

    int temp = *a;
    *a = *b;
    *b = temp;
}