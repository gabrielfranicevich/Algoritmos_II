#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(){
    stack s=malloc(sizeof(struct _s_stack));
    if (s == NULL) {fprintf(stderr,"stack allocation failed\n");exit(EXIT_FAILURE);}
    s->elems=malloc(sizeof(stack_elem));
    if (s->elems == NULL) {fprintf(stderr,"elem allocation failed\n");exit(EXIT_FAILURE);}
    s->size=0;
    s->capacity=1;
    return s;
}
bool invrep(stack s){
    return (s!=NULL && s->size<=s->capacity);
}
stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if (s->size==s->capacity)
    {
        s->capacity=2*(s->capacity);
        s->elems=realloc(s->elems,s->capacity*sizeof(stack_elem));
        if (s->elems == NULL) {fprintf(stderr,"reallocation failed\n");exit(EXIT_FAILURE);}
    }
    s->elems[s->size]=e;
    s->size++;
    return s;
}
stack stack_pop(stack s){
    assert(invrep(s));
    if (s->size == 0) {fprintf(stderr,"stack_pop fail: empty stack\n");exit(EXIT_FAILURE);}
    s->size--;
    return s;
}
unsigned int stack_size(stack s){
    assert(invrep(s));
    return s->size;
}
stack_elem stack_top(stack s){
    assert(invrep(s));
    if (s->size == 0) {fprintf(stderr,"stack_top fail: empty stack\n");exit(EXIT_FAILURE);}
    return s->elems[s->size-1];
}
bool stack_is_empty(stack s){
    assert(invrep(s));
    return (s->size==0);
}
stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *arr=malloc(s->size*sizeof(stack_elem));
    if (arr == NULL) {fprintf(stderr,"array allocation failed\n");exit(EXIT_FAILURE);}
    for (size_t i = 0; i < s->size; i++)
    {
        arr[i]=s->elems[i];
    }
    return arr;
}
stack stack_destroy(stack s){
    assert(invrep(s));
    free(s->elems);
    free(s);
    return NULL;
}