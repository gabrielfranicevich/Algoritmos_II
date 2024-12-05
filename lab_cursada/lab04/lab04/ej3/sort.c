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

bool goes_before(player_t x, player_t y){
    return (x->rank <= y->rank);
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    for (unsigned int i = 0; i < length - 1; i++) {
        if (!goes_before(atp[i], atp[i + 1])) {
            printf("en los indices %u y %u, %u no va antes que %u\n", i, i + 1, atp[i]->rank, atp[i + 1]->rank);
            return false;
        }
    }
    return true;
}

static void swap(player_t a[], unsigned int x, unsigned int y) {
    player_t tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der){
    unsigned int piv = izq, i = izq + 1, j = der;
    while (i <= j){
        if (goes_before(a[i], a[piv])){
            i++;
        }
        if (i <= j && goes_before(a[piv], a[j])){
            j--;
        }
        if (i <= j && goes_before(a[piv], a[i]) && goes_before(a[j], a[piv])){
            swap(a, i, j);
            i++; j--;
        }
    }
    swap(a, piv, j);
    piv = j;
    return piv;
}

static void rec_sort(player_t a[], unsigned int izq, unsigned int der){
    if (der > izq){
        unsigned int piv = partition(a, izq, der);
        if(izq < piv) rec_sort(a, izq, piv - 1u);
        rec_sort(a, piv + 1u, der);
    }
}

void sort(player_t a[], unsigned int length) {
    if (length) {
        rec_sort(a, 0u, length - 1u);
    }
}