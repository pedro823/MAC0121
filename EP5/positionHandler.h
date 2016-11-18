#ifndef __POSHANDLER_H__
#define __POSHANDLER_H__

typedef struct {
    char c;
    int visited;
} matCell;

typedef struct {
    unsigned char i, j;
} pos;

typedef matCell** matrix;

typedef struct {
    pos x;
    double value;
} valuedPos;

typedef struct {
    pos* v;
    int size;
} posList;

typedef struct {
    valuedPos* v;
    int top;
} valueList;


posList poslist_create(int size);

valueList valuelist_create();

void valuelist_append(valueList list, valuedPos x);

matrix matrix_create();

void matrix_print(matrix m);

void valuelist_sort(valueList list);

void valuelist_destroy(valueList list);

#endif
