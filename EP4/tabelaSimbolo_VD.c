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


void stable_destroy_vd(STable table) {
    free(table->vector);
    free(table);
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
/*
void stable_quickSort_o(STable table, int start, int end) {
    return;
}
*/

void stable_merge_o(STable table, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0, aux;
    STable aux;
    aux = (STable) malloc(sizeof(struct stable_v));
    aux.v->vector = (STable) malloc((end - start + 1) * sizeof(TableEntry));
    while(i <= mid && j <= end) {
        if(table.v->vector[i].data <= table.v->vector[j].data)
            aux.v->vector[k++] = table.v->vector[i++];
        else
            aux.v->vector[k++] = table.v->vector[j++];
    }
    while(i <= mid)
        aux.v->vector[k++] = table.v->vector[i++];
    while(j <= end)
        aux.v->vector[k++] = table.v->vector[j++];
    for(i = start; i <= end; i++)
        table.v->vector[i] = aux.v->vector[i - ini];
    stable_destroy_vd(aux);
}

void stable_sort_o(STable table, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        stable_sort_o(table, start, mid);
        stable_sort_o(table, mid + 1, end);
        stable_merge_o(table, start, mid, end);
    }
}

void stable_merge_a(STable table, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0, aux;
    STable aux;
    aux = (STable) malloc(sizeof(struct stable_v));
    aux.v->vector = (STable) malloc((end - start + 1) * sizeof(TableEntry));
    while(i <= mid && j <= end) {
        if(strcmp(table.v->vector[i].key, table.v->vector[j].key) <= 0)
            /* ptr1 is smaller */
            aux.v->vector[k++] = table.v->vector[i++];
        else
            /* ptr2 is smaller */
            aux.v->vector[k++] = table.v->vector[j++];
    }
    while(i <= mid)
        aux.v->vector[k++] = table.v->vector[i++];
    while(j <= end)
        aux.v->vector[k++] = table.v->vector[j++];
    for(i = start; i <= end; i++)
        table.v->vector[i] = aux.v->vector[i - ini];
    stable_destroy_vd(aux);
}

void stable_sort_a(STable table, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        stable_sort_a(table, start, mid);
        stable_sort_a(table, mid + 1, end);
        stable_merge_a(table, ini, mid, end);
    }
}

/*
void stable_quickSort_a(STable table, int start, int end) {
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
*/

void stable_print_vd(STable table, const char mode) {
    STable temp;
    int i;
    temp = (STable) malloc(sizeof(struct stable_s));
    temp.v->vector = (TableEntry*) malloc(table.v->top * sizeof(TableEntry));
    temp.v->top = table.v->top;
    for(i = 0; i < table->top; i++)
        temp.v->vector[i] = table.v->vector[i];
    if(mode == 'O') {
        stable_sort_o(temp, 0, table->top - 1);
    }
    else {
        stable_sort_a(temp, 0, table->top - 1);
    }
    for(i = 0; i < table->top; i++) {
        printf("%s : %d", temp.v->vector[i].key, temp.v->vector[i].data);
    }
    stable_destroy_vd(temp);
}