#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
 
struct _s_stack {
    stack_elem elem;      
    stack next;    
    unsigned int size;
};

bool invrep(stack s){
    return (s!=NULL);
}

stack stack_empty(){
    stack s= malloc(sizeof(struct _s_stack));
    s->next=NULL;
    s->size=0;
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    stack new = (stack)malloc(sizeof(struct _s_stack));
    if (new == NULL) {
        fprintf(stderr, "alloc fail\n");
        exit(EXIT_FAILURE);
    }
    new->elem = e;
    new->next = s;
    new->size = s->size + 1;
    return new;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    stack next = s->next;
    free(s);
    return next;
}

unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
    }

stack_elem stack_top(stack s) {
    if (s == NULL) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE); 
    }
    return s->elem;
}

bool stack_is_empty(stack s){
    assert(invrep(s));
    return (s->size==0);}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *arr=malloc(s->size * sizeof(stack_elem));
    stack tmp = s;
    unsigned int i=0;
    while (tmp->size>0)
    {
        arr[i]=stack_top(tmp);
        tmp=tmp->next;
        i++;
    }
    return arr;
}

stack stack_destroy(stack s) {
    while (s != NULL && s->next != NULL) {
        s = stack_pop(s);
    }
    if (s != NULL) {
        free(s);
    }
    return NULL;
}
