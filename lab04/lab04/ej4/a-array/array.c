#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_SIZE 7 // Predefino el tamaño del array en 7


// Esta funcion imprime los elementos del arreglo
static void print_array(int a[], size_t length) {
    assert(length > 0); // Termina el programa si el tamaño es menor o igual a 0
    printf("[ %d", a[0]);
    for (size_t i=1; i<length; i++) {
        printf(", %d", a[i]);
    }
    printf("]\n");
}

/* El fin de este programa es que mediante el puntero p se inicialice arr en 0 */
int main(void) {
    // Declaro un arreglo arr de 7 elementos
    int arr[ARRAY_SIZE] = {7, 4, 1, 3, 9, 3, 5};
    
    // Declaro un puntero p
    int *p=NULL;

    // Imprimo el arreglo original
    printf("before: ");
    print_array(arr, ARRAY_SIZE);
   
    // Uso el ciclo para cambiar todos los elementos por 0
    for (unsigned int i=0u; i < ARRAY_SIZE; i++) {
        p = arr; // p toma el valor del arreglo
        p[i] = 0; // y mediante i hago que todos los elementos sean 0
    }

    printf("after : ");
    print_array(arr, ARRAY_SIZE);

    return EXIT_SUCCESS;
}