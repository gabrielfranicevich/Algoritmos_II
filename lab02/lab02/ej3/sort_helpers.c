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