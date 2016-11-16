#ifndef __STACK_H__
#define __STACK_H__

typedef struct {
    char i, j;
} pos;

typedef struct {
    pos* v;
    int size, top;
} stack;

stack stack_create();
void stack_insert(stack s, pos x);
pos stack_pop(stack s);
pos stack_top(stack s);
void stack_destroy(stack s);


#endif
