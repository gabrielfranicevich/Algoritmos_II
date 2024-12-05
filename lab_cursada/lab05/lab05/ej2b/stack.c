#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    stack next;
    nat size;
};

stack stack_empty() {
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack push = malloc(sizeof(struct _s_stack));
    push->elem = e;
    push->next = s;
    push->size = stack_size(s) + 1;
    return push;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    stack pop = s->next;
    free(s);
    return pop;
}

nat stack_size(stack s){
    return (s != NULL  ? s->size : 0);
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem * stack_to_array(stack s){
    stack_elem * array = malloc(sizeof(stack_elem) * stack_size(s));
    stack aux = s;
    int i = 0;
    while(aux != NULL){
        array[i] = stack_top(aux);
        aux = aux->next;
        i++;
    }
    return array;
}

stack stack_destroy (stack s) {
    while (!stack_is_empty(s)){
        s = stack_pop(s);
    }
    return NULL;
}