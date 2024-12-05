#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty() {
    stack s = malloc(sizeof(struct _s_stack));
    s->size = 0;
    s->capacity = 1;
    s->elems = malloc(sizeof(stack_elem));;
    return s;
}

bool invrep(stack s){
    return (s != NULL && (s->size <= s->capacity));
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if (s->size == s->capacity){
        s->elems = realloc(s->elems, (s->capacity * 2) * sizeof(stack_elem));
        s->capacity = s->capacity * 2;
    }
    s->elems[s->size] = e;
    s->size++;
    
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    s->size--;
    return s;
}

unsigned int stack_size(stack s){
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s){
    assert(invrep(s));
    return s->size == 0;
}

stack_elem * stack_to_array(stack s){
    assert(invrep(s));
    unsigned int i = 0, size = stack_size(s);
    stack_elem * array = malloc(sizeof(stack_elem) * size);
    while(i < size){
        array[i] = s->elems[size - i - 1];
        i++;
    }
    return array;
}

stack stack_destroy (stack s) {
    assert(invrep(s));
    free(s->elems);
    free(s);
    return NULL;
}