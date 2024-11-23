/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"




typedef struct _player_t {
    char name[100];
    char country[4];
    unsigned int rank;
    unsigned int age;
    unsigned int points;
    unsigned int tournaments;
} * player_t; // player_t is an alias of struct _player_t 

// esta definicion es un tipo de puntero a la estructura player_t



/* Chequea si el jugador x va antes que el jugador y */
bool goes_before(player_t x, player_t y){ // recibe dos punteros a estructuras player_t 
    return (&x->rank <= &y->rank); 
    // uso el -> para que una variable de tipo puntero, apunte a una estructura de datos
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);

    /* Esta funcion verifica si el arreglo esta ordenado de menor a mayor, 
    segun el criterio de goes_before */

    /* Itera a traves del arrelo comparando los elementos adyacentes, 
    si esta ordenado devuelve true*/

    /* Esta fucnion no utiliza punteros directamente pero trabaja con un arreglo de punteros
    a la estructura player_t */

}

static void swap(player_t a[], unsigned int x, unsigned int y) {
    player_t tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;

    /* Esta funcion recibe dos parametros x e y, y tambien un arreglo a de tipo 
    puntero a la estructura player_t */
}

static void insert(player_t a[], unsigned int i) {
    for (unsigned int j = i; 1 <= j; j--) {
        if (goes_before(a[j],a[j-1])) swap(a, j, j-1);
    }

    /* Esta funcion inserta el elemento en la posicion i en su posicion correcta.
    asumiendo que los elementos anteriores ya estan ordenados. Compara el elemento actual
    con los anteriores*/
}

void sort(player_t a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}

/*
La función sort implementa un algoritmo de ordenamiento por inserción.

Empieza desde el segundo elemento del arreglo (i = 1).
En cada iteración del bucle, insert coloca el elemento a[i] en la posición correcta 
dentro de la parte del arreglo que ya está ordenada.

Repite este proceso hasta que todos los elementos estén en su lugar, 
resultando en un arreglo completamente ordenado.

Este método es sencillo pero eficiente para arreglos pequeños o casi ordenados, 
aunque no es el más eficiente para arreglos grandes en comparación con otros algoritmos 
de ordenamiento como quicksort o mergesort.
*/

// Es mas rapido ya que al usar punteros se reduce la sobrecarga de memoria
// y se realizan las opperaciones de forma directa
