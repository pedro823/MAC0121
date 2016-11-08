#include "tabelaSimbolo_VO.h"
#include "stable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_vd() {
    STable new;
    new = (STable) malloc(sizeof(struct stable_v));
    new.v->vector = (TableEntry*) malloc(1024*sizeof(TableEntry));
    new.v->max = 1024;
    new.v->top = 0;
    return new;
}

void stable_reallocate_vd(STable table) {
    STable new;
    int i;
    new = (STable) malloc(sizeof(struct stable_v));
    new.v->vector = (TableEntry*)malloc(2 * table.v->max * sizeof(TableEntry));
    for(i = 0; i < table->top; i++) {
        new.v->vector[i] = table.v->vector[i];
    }
    new.v->top = table.v->top;
    new.v->max = 2 * table.v->max;
    free(table->vector);
    free(table);
    table = new;
}

Result stable_insert_vd(STable table, char* key) {
    int i;
    Result ret;
    for(i = 0; i < table.v->top; i++) {
        if(strcmp(key, table.v->vector[i].key) == 0) {
            ret.new = 0;
            ret.data = &(table.v->vector[i].data);
            return ret;
        }
    }
    if(table.v->top == table.v->max)
        stable_reallocate_vd(table);
    table->vector[table.v->top].key = key;
    table->vector[table.v->top].data = 0;
    ret.new = 1;
    ret.data = &(table.v->vector[table->top++].data);
    return ret;
}

int* stable_find_vd(STable table, char* key) {
    int i;
    for(i = 0; i < table->top; i++) {
        if(strcmp(key, table.v->vector[i].key) == 0) {
            return &(table.v->vector[i].data);
        }
    }
    return NULL;
}

void stable_quickSort_o(STable table, int start, int end) {
    /* Ocorrências */
    return;
}

void stable_quickSort_a(STable table, int start, int end) {
    /* Alfabética */
    TableEntry aux;
    char* pivot;
    int i, j;
    pivot = table.v->vector[start].key;
    i = start;
    j = end;
    while(i < j) {
        while(strcmp(table.v->vector[j].key, pivot) > 0 && j > i)
            j--;
        while(strcmp(table.v->vector[i].key, pivot) < 0 && j > i)
            i++;
        if(j > i);
    }
}

void stable_print_vd(STable table, const char mode) {
    STable temp;
    int i;
    temp = (STable) malloc(sizeof(struct stable_s));
    temp.v->vector = (TableEntry*) malloc(table.v->top * sizeof(TableEntry));
    temp.v->top = table.v->top;
    for(i = 0; i < table->top; i++)
        temp.v->vector[i] = table.v->vector[i];
    if(mode == 'O') {
        stable_quickSort_o(temp, 0, table->top - 1);
    }
    else {
        stable_quickSort_a(temp, 0, table->top - 1);
    }
    for(i = 0; i < table->top; i++) {
        printf("%s : %d", temp.v->vector[i].key, temp.v->vector[i].data);
    }
}

void stable_destroy_vd(STable table) {
    free(table->vector);
    free(table);
}
