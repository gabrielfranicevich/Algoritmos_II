#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

bool goes_before(int x, int y) {
    return x <= y;
}

bool array_is_sorted(int a[], unsigned int length) {
    for (unsigned int i = 0; i < length - 1; i++) {
        if (!goes_before(a[i], a[i + 1])) {
            return false;
        }
    }
    return true;
}

void swap(int a[], unsigned int i, unsigned int j) {
    if (i != j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

unsigned int partition(int a[], unsigned int izq, unsigned int der){
    unsigned int piv = izq, i = izq + 1, j = der;
    while (i <= j){
        if (i <= j && goes_before(a[i], a[piv])){
            i++;
        }
        if (i <= j && !goes_before(a[j], a[piv])){
            j--;
        }
        if (i <= j && !goes_before(a[i], a[piv]) && goes_before(a[j], a[piv])){
            swap(a, i, j);
            i++; j--;
        }
    }
    swap(a, piv, j);
    piv = j;   
    return piv;
}