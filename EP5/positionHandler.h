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
    float value;
} vPos;

typedef struct {
    pos* v;
    int size, top;
} posList;

typedef struct {
    vPos* v;
    int top;
} valueList;


posList poslist_create(int size);

void poslist_destroy(posList list);

valueList valuelist_create();

void valuelist_append(valueList list, vPos x);

matrix matrix_create();

void matrix_destroy(matrix m);

void matrix_print(matrix m);

void valuelist_sort(valueList list);

void valuelist_destroy(valueList list);

#endif
