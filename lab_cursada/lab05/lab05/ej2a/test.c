#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "reverse/array_helpers.h"

void test_push(stack *s){
    printf("\nPush Test: \n");


    stack_elem fst = 1, snd = 2, trd = 3;

    *s = stack_push(*s, fst);
    printf("  Size: %d, ", stack_size(*s));
    printf("Top: %d\n", stack_top(*s));
    
    
    
    *s = stack_push(*s, snd);
    printf("  Size: %d, ", stack_size(*s));
    printf("Top: %d\n", stack_top(*s));
    
    *s = stack_push(*s, trd);
    printf("  Size: %d, ", stack_size(*s));
    printf("Top: %d\n", stack_top(*s));
}

void test_pop(stack *s){
    printf("\nPop Test: \n");

    *s = stack_pop(*s);
    printf("  Size: %d, ", stack_size(*s));
    printf("Top: %d\n", stack_top(*s));

    *s = stack_pop(*s);
    printf("  Size: %d, ", stack_size(*s));
    printf("Top: %d\n", stack_top(*s));
}    

int main(){
    printf("\nStack Test: \n");

    stack s = stack_empty();
    
    bool empty = stack_is_empty(s);
    empty ? printf("\n  initial size: %d\n", stack_size(s)) : fprintf(stderr, "failed\n");
    
    test_push(&s);  //  &s = dirección del stack
    printf("\n  size after push: %d\n", stack_size(s));
    
    empty = stack_is_empty(s);
    !empty ? printf("\n    stack is not empty anymore \n") : fprintf(stderr, "failed\n");

    test_pop(&s);
    test_push(&s);
    stack_elem *array = stack_to_array(s);
    array_dump(array, stack_size(s));


    s = stack_destroy(s);
    free(array);


    printf("\n");
    
    return 0;
}
