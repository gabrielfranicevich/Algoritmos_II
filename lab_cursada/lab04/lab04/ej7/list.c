#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node {
    list_elem elem;
    list next;
};

list empty_list(void) {
    return NULL;
}

list addl(list l, list_elem e) {
    list new = malloc(sizeof(struct node));
    new->elem = e;
    new->next = l;
    return new;
}

list destroy_list(list l){
    list aux;
    while (l != NULL) {
        aux = l;
        l = l->next;
        free(aux);
    }
    return NULL;
}

bool is_list_empty(list l) {
    return l == NULL;
}

list_elem head(list l) {
    assert(!is_list_empty(l));
    return l->elem;
}

list tail(list l) {
    assert(!is_list_empty(l));
    list tail = l->next;
    free(l);
    return tail;
}

//  función addr recursiva
/*
list addr(list l, list_elem e) {
    if (is_list_empty(l)) {
        return addl(l, e);
    } 
    l->next = addr(l->next, e);
    return l;
}
*/

list addr(list l, list_elem e) {
    list p, q;
    q = malloc(sizeof(struct node));
    q->elem = e;
    q->next = NULL;
    if (is_list_empty(l)) {
        return q;
    }
    p = l;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = q;
    return l;
}

nat list_length(list l){
    list p;
    nat n = 0;
    p = l;
    while (p != NULL) {
        ++n;
        p = p->next;
    }
    return n;
}

list list_concat(list l1, list l2){
    list aux;
    aux = l1;
    if (is_list_empty(l1)) {
        return l2;
    }
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = l2;
    return l1;
}

list_elem list_index(list l, nat n){
    nat i = 0;
    while (i < n) {
        l = l->next;
        ++i;
    }
    return l->elem;
}

list take(list l, nat n){
    nat i = 0;
    while (i < n) {
        l = l->next;
        ++i;
    }
    l->next = destroy_list(l->next);
    return l;
}

list drop(list l, nat n){
    nat i = 0;
    list aux;
    while (i < n){
        aux = l;
        l = l->next;
        free(aux);
        ++i;
    }
    return l;
}

list list_copy(list l1){
    list l2;
    while(l1 != NULL){
        l2 = addr(l2, l1->elem);
        l1 = l1->next;
    }
    return l2;
}