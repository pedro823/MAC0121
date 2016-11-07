#include "tabelaSimbolo_VO.h"
#include "stable.h"
#include <stdio.h>

STable stable_create_vd() {
    STable new;
    new = (Stable) malloc(sizeof(struct stable_s));
    new->vector = (TableEntry*) malloc(1024*sizeof(TableEntry));
    new->max = 1024;
    new->top = 0;
    return new;
}

void stable_reallocate_vd(STable table) {
    STable new;
    int i;
    new = (STable) malloc(sizeof(struct stable_s));
    new->vector = (TableEntry*) malloc(2 * table->max * sizeof(TableEntry));
    for(i = 0; i < table->top; i++) {
        new->vector[i] = table->top[i];
    }
    new->top = table->top;
    new->max = 2 * table->max;
    free(table->vector);
    free(table);
    table = new;
}

Result stable_insert_vd(STable table, char* key) {
    int i;
    Result ret;
    for(i = 0; i < table->top; i++) {
        if(strcmp(key, table->vector[i].key) == 0) {
            ret.new = 0;
            ret.data = &(table->vector[i].data);
            return ret;
        }
    }
    if(table->top == table->max)
        stable_reallocate_vd(table);
    table->vector[table->top].key = key;
    table->vector[table->top].data = 0;
    ret.new = 1;
    ret.data = &(table->vector[table->top++]);
    return ret;
}

int* stable_find_vd(STable table, char* key) {
    int i;
    for(i = 0; i < table->top; i++) {
        if(strcmp(key, table->vector[i].key) == 0) {
            return &(table.vector[i].data);
        }
    }
    return NULL;
}

void stable_quickSort_o(STable table. int start, int end) {
    /* Ocorrências */
}

void stable_quickSort_a(STable table, int start, int end) {
    /* Alfabética */
    TableEntry aux;
    char* pivot;
    int i, j;
    pivot = table->vector[ini].key;
    i = start;
    j = end;
    while(i < j) {
        while(strcmp(table->vector[j].key, pivot) > 0 && j > i)
            j--;
        while(strcmp(table->vector[i].key, pivot) < 0 && j > i)
            i++;
        if(j > i)

    }
}

void stable_print_vd(STable table, const char mode) {
    STable temp;
    int i;
    temp = (STable) malloc(struct stable_s);
    temp->vector = (TableEntry*) malloc(table->top * sizeof(TableEntry));
    temp->top = table->top;
    for(i = 0; i < table->top; i++)
        temp->vector[i] = table->vector[i];
    if(mode == 'O') {
        stable_quickSort_o(temp)
    }
    else if(mode == 'A') {
        stable_quickSort_a(temp, 0, table->top - 1)
    }
    for(i = 0; i < table->top; i++) {
        printf("%s : %d", temp->vector[i].key, temp->vector[i].data);
    }
}

void stable_destroy_vd(STable table) {
    free(table->vector);
    free(table);
}
