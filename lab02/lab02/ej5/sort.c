#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int piv, j, i;
    piv = izq;
    i = izq + 1; j = der;

    while (i <= j){
        if(goes_before(a[i], a[piv])){
            i++;
        }
        
        //  compruebo si j es mayor que i porque se puede cambiar en el if anterior
        if(i <= j && goes_before(a[piv], a[j])){
            j--;
        }

        //  compruebo si j es mayor que i porque se puede cambiar en el if anterior
        if(i <= j && goes_before(a[piv], a[i]) && goes_before(a[j], a[piv])) {
            swap(a, i, j);
            i++; j--;
        }
    }
    
    swap(a, izq, j);
    return j;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    if (izq < der){
        unsigned int piv = partition(a, izq, der);
        if (piv){
            quick_sort_rec(a, izq, piv - 1);
        }
        quick_sort_rec(a, piv + 1, der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


