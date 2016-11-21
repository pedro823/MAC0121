#include "positionHandler.h"
#include <stdlib.h>
#include <stdio.h>

posList poslist_create(int size) {
    posList new;
    new.v = malloc(size * sizeof(pos));
    new.size = size;
    new.top = 0;
    return new;
}

void poslist_destroy(posList list) {
    free(list.v);
}

valueList valuelist_create() {
    valueList new;
    /* Somente 196 serão usados, 4 para folga */
    new.v = malloc(200 * sizeof(vPos));
    new.top = 0;
    return new;
}

void valuelist_destroy(valueList list) {
    free(list.v);
}

void valuelist_append(valueList list, vPos x) {
    list.v[list.top++] = x;
}

matrix matrix_create() {
    matrix new;
    int i, j;
    new = malloc(14*sizeof(matCell*));
    for(i = 0; i < 14; i++)
        new[i] = malloc(14*sizeof(matCell));
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            new[i][j].c = '-';
            new[i][j].visited = 0;
        }
    }
    return new;
}

void matrix_print(matrix m) {
    int i, j;
    printf(" 0 1 2 3 4 5 6 7 8 9 A B C D\n");
    for(i = 0; i < 14; i++) {
        for(j = 0; j < i; j++)
            fprintf(stderr, " ");
        fprintf(stderr, "%c ", "0123456789ABCD"[i]);
        for(j = 0; j < 14; j++) {
            fprintf(stderr, "%c ", m[i][j].c);
        }
        fprintf(stderr, "\n");
    }
}

void valuelist_merge(valueList list, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0;
    valueList aux;
    aux = valuelist_create();
    while(i <= mid && j <= end)
        if(list.v[i].value >= list.v[j].value)
            aux.v[k++] = list.v[i++];
        else
            aux.v[k++] = list.v[j++];
    while(i <= mid)
        aux.v[k++] = list.v[i++];
    while(j <= end)
        aux.v[k++] = list.v[j++];
    for(i = start; i <= end; i++)
        list.v[i] = aux.v[i - start];
    valuelist_destroy(aux);
}

void valuelist_mergesort(valueList list, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        valuelist_mergesort(list, start, mid);
        valuelist_mergesort(list, mid + 1, end);
        valuelist_merge(list, start, mid, end);
    }
}

void valuelist_sort(valueList list) {
    valuelist_mergesort(list, 0, list.top - 1);
}
