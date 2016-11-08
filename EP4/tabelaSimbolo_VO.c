#include "tabelaSimbolo_VO.h"
#include "stable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_vo() {
    STable new;
    new = (STable) malloc(sizeof(struct stable_s));
    new->vector = (TableEntry*) malloc(1024 * sizeof(TableEntry));
    new->max = 1024;
    new->top = 0;
    return new;
}

void stable_reallocate_vo(STable table) {
    STable new;
    int i;
    new = (STable) malloc(sizeof(struct stable_s));
    new->vector = (TableEntry*) malloc(2 * table-> max * sizeof(TableEntry));
    for(i = 0; i < table->top; i++) {
        new->vector[i].key = table->vector[i].key;
        new->vector[i].data = table->vector[i].data;
    }
    new->top = table->top;
    new->max = 2 * table->max;
    stable_destroy_vo(table);
    table = new;
}

Result stable_insert_vo(STable table, char* key) {
    int ini = 0, fim = table->top, mid, res, i;
    Result ret;
    while(ini <= fim) {
        mid = (ini + fim) / 2;
        res = strcmp(table->vector[mid].key, key);
        if(res == 0) {
            ret.new = 0;
            ret.data = &(table->vector[mid].data);
            return ret;
        }
        else if(res < 0)
            ini = mid + 1;
        else
            fim = mid - 1;
    }
    /* inserir entre fim e ini*/
    if(table->top == table->max)
        stable_reallocate_vo(table);
    /* Empurra todos os da frente para + 1 */
    for(i = table->top + 1; i > ini; i--) {
        table->vector[i] = table->vector[i - 1];
    }
    table->vector[ini].key = key;
    table->vector[ini].data = 0;
    table->top++;
    ret.new = 1;
    ret.data = &(table->vector[ini].data);
    return ret;
}

int* stable_find_vo(STable table, char* key) {
    int ini = 0, fim = table->top, res, mid;
    while(ini <= fim) {
        mid = (ini + fim) / 2;
        res = strcmp(table->vector[mid].key, key);
        if(res == 0)
            return &(table->vector[mid].data);
        else if(res < 0)
            ini = mid + 1;
        else
            fim = mid - 1;
    }
    return NULL;
}

void stable_merge_vo_o(STable table, int ini, int mid, int fim) {
    int i = 0, j = mid + 1, k = 0, res;
    STable aux;
    aux = (STable) malloc(sizeof(struct stable_s));
    aux->vector = (TableEntry*) malloc((fim - ini + 1) * sizeof(TableEntry));
    while(i <= mid && j <= fim) {
        res = strcmp(table->vector[i].key, table->vector[j].key);
        if(res <= 0)
            aux->vector[k++] = table->vector[i++];
        else
            aux->vector[k++] = table->vector[j++];
    }
    while(i<= mid)
        aux->vector[k++] = table->vector[i++];
    while(j <= fim)
        aux->vector[k++] = table->vector[j++];
    for(i = ini; i <= fim; i++)
        table->vector[i] = aux->vector[i];
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
        for(i = 0; i < table->top; i++)
            printf("%s : %d\n", table->vector[i].key, table->vector[i].data);
    else {
        temp = (STable) malloc(table->top * sizeof(struct stable_s));
        temp->vector = (TableEntry*) malloc(table->top * sizeof(TableEntry));
        for(i = 0; i < table->top; i++)
            temp->vector[i] = table->vector[i];
        temp->top = table->top;
        temp->max = table->top;
        stable_sort_vo_o(temp, 0, temp->top-1);
        for(i = 0; i < table->top; i++)
            printf("%s : %d\n", temp->vector[i].key, temp->vector[i].data);
        stable_destroy_vo(temp);
    }
}

void stable_destroy_vo(STable table) {
    free(table->vector);
    free(table);
}
