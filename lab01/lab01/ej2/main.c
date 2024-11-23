/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[],
                             unsigned int max_size) {
    //  se pide por consola ingresar el tamaño del array
    printf("ingresar largo del array\n");
    unsigned int size;
    scanf("%u", &size);
    
    //  error si sobrepasa el máximo
    if (size > max_size) {
        printf("el largo maximo es %d", MAX_SIZE);
        exit(EXIT_FAILURE);
    }

    //  se pide ingresar los elementos del array
    printf("ingresar elementos\n");
    unsigned int i = 0u;
    while (i < size) {
        scanf("%d", &array[i]);
        i = i + 1;
    }
    return size;
}

void array_dump(int a[], unsigned int length) {
    //  se imprime [ y el primer elemento del array
    printf("[%d", a[0]);
    
    //  se imprimen los demás elementos
    //  ", e_i" para que al final quede [e_1, e_1, ..., e_n]
    unsigned int i = 1u;
    while (i < length) {
        printf(", %d", a[i]);
        i = i + 1;
    }
    
    // se imprime ] para cerrar el array
    printf("]\n");
}


int main() {
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the standard input to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
