#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

/* Aplico el algortimo de insercion visto en el teorico, con la diferencia de que utilizamos goes_before
para comparar, le resto uno a los valores de los indices, ya que en el teorico se utiliza otro criterio */
static void insert(int a[], unsigned int i) {
    //  comparo el elemento i con el elemento anterior
    //  hasta que el elemento anterior no sea mayor o se termine el array
    while (i > 0 && goes_before(a[i], a[i - 1])) {
        //  si el elemento anterior es mayor, los intercambio
        swap(a, i, i - 1);
        i--;
    }   
}

void insertion_sort(int a[], unsigned int length) {
    //  para todos los elementos del array desde el 2do
    for (unsigned int i = 1; i < length; i++){
        assert(array_is_sorted(a, i));
        //  comparo todos los elementos con sus anteriores y los intercambio de ser necesario
        insert(a, i);
    }
}
