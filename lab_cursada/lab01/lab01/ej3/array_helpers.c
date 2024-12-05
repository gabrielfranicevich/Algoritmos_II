#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    //  se abre el archivo en la dirección obtenída
    FILE *file = fopen(filepath, "r");

    //  error si el archivo no existe
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    //  se obtiene el tamaño del array
    //  (se lee el primer caracter)
    unsigned int size;
    fscanf(file, "%u", &size);

    //  error si el tamaño del array es mayor al máximo
    if (size > max_size) {
        exit(EXIT_FAILURE);
    }

    //  se leen ´tamaño´ caracteres del archivo 
    //  se almacenan en las posiciones ´0´ a ´tamaño - 1´ del array
    unsigned int i = 0u;
    while (i < size) {
        fscanf(file, "%d", &array[i]);
        i = i + 1;
    }

    //  se cierra el archivo y se devuelve el tamaño
    fclose(file);
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