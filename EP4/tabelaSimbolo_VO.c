#include "tabelaSimbolo_VO.h"
#include "stable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_vo() {
    STable new;
    new.v = malloc(sizeof(struct stable_v));
    new.v->vector = (TableEntry*) malloc(1024 * sizeof(TableEntry));
    new.v->max = 1024;
    new.v->top = 0;
    return new;
}

void stable_reallocate_vo(STable table) {
    STable new;
    int i;
    new.v = malloc(sizeof(struct stable_v));
    new.v->vector = (TableEntry*)malloc(2 * table.v->max * sizeof(TableEntry));
    for(i = 0; i < table.v->top; i++) {
        new.v->vector[i].key = table.v->vector[i].key;
        new.v->vector[i].data = table.v->vector[i].data;
    }
    new.v->top = table.v->top;
    new.v->max = 2 * table.v->max;
    stable_destroy_vo(table);
    table = new;
}

Result stable_insert_vo(STable table, char* key) {
    int ini = 0, fim = table.v->top, mid, res, i;
    Result ret;
    while(ini < fim) {
        mid = (ini + fim) / 2;
        res = strcmp(table.v->vector[mid].key, key);
        if(res == 0) {
            ret.new = 0;
            ret.data = &(table.v->vector[mid].data);
            return ret;
        }
        else if(res < 0)
            ini = mid + 1;
        else
            fim = mid;
    }
    /* inserir entre fim e ini*/
    if(table.v->top == table.v->max)
        stable_reallocate_vo(table);
    /* Empurra todos os da frente para + 1 */
    for(i = table.v->top + 1; i > ini; i--) {
        table.v->vector[i] = table.v->vector[i - 1];
    }
    table.v->vector[ini].key = malloc(strlen(key) * sizeof(char));
    strcpy(table.v->vector[ini].key, key);
    table.v->vector[ini].data = 0;
    table.v->top++;
    ret.new = 1;
    ret.data = &(table.v->vector[ini].data);
    return ret;
}

int* stable_find_vo(STable table, char* key) {
    int ini = 0, fim = table.v->top, res, mid;
    while(ini <= fim) {
        mid = (ini + fim) / 2;
        res = strcmp(table.v->vector[mid].key, key);
        if(res == 0)
            return &(table.v->vector[mid].data);
        else if(res < 0)
            ini = mid + 1;
        else
            fim = mid - 1;
    }
    return NULL;
}

void stable_merge_vo_o(STable table, int ini, int mid, int fim) {
    int i = ini, j = mid + 1, k = 0;
    STable aux;
    aux.v = malloc(sizeof(struct stable_v));
    aux.v->vector = (TableEntry*) malloc((fim - ini + 1) * sizeof(TableEntry));
    while(i <= mid && j <= fim) {
        if(table.v->vector[i].data > table.v->vector[j].data)
            aux.v->vector[k++] = table.v->vector[i++];
        else
            aux.v->vector[k++] = table.v->vector[j++];
    }
    while(i<= mid)
        aux.v->vector[k++] = table.v->vector[i++];
    while(j <= fim)
        aux.v->vector[k++] = table.v->vector[j++];
    for(i = ini; i <= fim; i++)
        table.v->vector[i] = aux.v->vector[i - ini];
    stable_destroy_vo(aux);
}

void stable_sort_vo_o(STable table, int ini, int fim) {
    int mid;
    if(ini < fim) {
        mid = (ini + fim) / 2;
        stable_sort_vo_o(table, ini, mid);
        stable_sort_vo_o(table, mid+1, fim);
        stable_merge_vo_o(table, ini, mid, fim);
    }
}

void stable_print_vo(STable table, const char mode) {
    STable temp;
    int i;
    if(mode == 'A')
        for(i = 0; i < table.v->top; i++)
            printf("%s : %d\n",
                table.v->vector[i].key, table.v->vector[i].data);
    else {
        temp.v = malloc(table.v->top * sizeof(struct stable_v));
        temp.v->vector = (TableEntry*) malloc(table.v->top*sizeof(TableEntry));
        for(i = 0; i < table.v->top; i++)
            temp.v->vector[i] = table.v->vector[i];
        temp.v->top = table.v->top;
        temp.v->max = table.v->top;
        stable_sort_vo_o(temp, 0, temp.v->top-1);
        for(i = 0; i < table.v->top; i++)
            printf("%s : %d\n", temp.v->vector[i].key, temp.v->vector[i].data);
        stable_destroy_vo(temp);
    }
}

void stable_destroy_vo(STable table) {
    free(table.v->vector);
    free(table.v);
}
