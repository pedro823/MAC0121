#include "stack.h"
#include <stdlib.h>

stack stack_create() {
    stack new;
    new.v = malloc(1024 * sizeof(pos));
    new.size = 1024;
    new.top = 0;
    return new;
}

stack stack_realloc(stack s) {
    stack new;
    int i;
    new.v = malloc(2 * s.size * sizeof(pos));
    new.size = 2 * s.size;
    for(i = 0; i < s.size; i++)
        new.v[i] = s.v[i];
    new.top = s.top;
    free(s.v);
    return new;
}

void stack_insert(stack s, pos x) {
    if(s.top == s.size)
        s = stack_realloc(s);
    s.v[s.top++] = x;
    
}

pos stack_pop(stack s) {
    pos nil;
    if(s.top) {
        return s.v[--s.top];
    }
    nil.i = -1;
    nil.j = -1;
    return nil;
}

pos stack_top(stack s) {
    return s.v[s.top - 1];
}

void stack_destroy(stack s) {
    free(s.v);
}
