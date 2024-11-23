#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


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

void quick_sort(int a[], unsigned int length) {
    if (length > 1) {
        //  quick sort rec con el primer elemendo a la izquierda y el último a la derecha
        quick_sort_rec(a, 0, length - 1);
    }
}

