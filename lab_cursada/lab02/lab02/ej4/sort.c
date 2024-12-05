#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

//  busca el número más chico a partir de una posición en el array
static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos], a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

//  se ordena buscando al más chico, después al segundo, etc
void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}

//  compara un elemento con sus anteriores, se mueve para atrás hasta que haya uno más chico
static void insert(int a[], unsigned int i) {
    //  comparo el elemento i con el elemento anterior
    //  hasta que el elemento anterior no sea mayor o se termine el array
    while (i > 0 && goes_before(a[i], a[i - 1])) {
        //  si el elemento anterior es mayor, los intercambio
        swap(a, i, i - 1);
        i--;
    }   
}

//  compara cada elemento con los anteriores, los va ordenando progresivamente
void insertion_sort(int a[], unsigned int length) {
    //  para todos los elementos del array desde el 2do
    for (unsigned int i = 1; i < length; i++){
        assert(array_is_sorted(a, i));
        //  comparo todos los elementos con sus anteriores y los intercambio de ser necesario
        insert(a, i);
    }
}

/**
 * compara todos los elementos con un pivot
 * los acomoda a la izquierda o derecha dependiendo de si son mayores o menores que el pivot
 * finalmente mueve al pivot a su posición final y devuelve su índice
 */
static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int piv, j, i;
    piv = izq;
    i = izq + 1; j = der;

    while (i <= j){
        //  se busca un numero a la izquierda del pivot 
        //  que no esté en su posición correcta con respecto a él
        if(goes_before(a[i], a[piv])){
            i++;
        }
        
        //  compruebo si j es mayor que i porque se puede cambiar en el if anterior
        if(i <=j && goes_before(a[piv], a[j])){
            j--;
        }

        //  si a[i] y a[j] están mal ubicados, se swapean
        if(i <= j && goes_before(a[piv], a[i]) && goes_before(a[j], a[piv])) {
            swap(a, i, j);
            i++; j--;
        }
    }

    //  j es la posición correcta para el pivote, 
    //  los más chicos están a la izquierda,
    //  los más grandes a la derecha
    swap(a, piv, j);
    piv = j;
    return piv;
}

//  selecciona un pivot, ordena los números a su izquierda y a su derecha
static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    if(der > izq){
        //  izq ≤ piv ≤ der
        unsigned int piv = partition(a, izq, der);

        //  elementos en a[izq, piv-1] ≤ a[piv]
        if (piv > 0) {
            quick_sort_rec(a, izq, piv - 1);
        }

        //  elementos en a[piv + 1, der] ≥ a[piv]
        quick_sort_rec(a, piv + 1, der);
    }
}

//  ordena eligiendo pivots, los números más grandes se mueven a la derecha, los más chicos a la izquierda
void quick_sort(int a[], unsigned int length) {
    if (length > 1) {
        //  quick sort rec con el primer elemendo a la izquierda y el último a la derecha
        quick_sort_rec(a, 0, length - 1);
    }
}