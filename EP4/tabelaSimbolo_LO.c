#include "stable.h"
#include "tabelaSimbolo_LO.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


STable stable_create_lo() {
    return NULL;
}

Result stable_insert_lo(STable* table, char* key) {
    Result ret;
    STable i, ant, new;
    if((*table).l != NULL) {
        i = (*table);
        ant.l = NULL;
        while(i.l != NULL) {
            if(strcmp(i.l->data.key, key) == 0) {
                ret.new = 0;
                ret.data = &(i.l->data.data);
                return ret;
            }
            /* Inserir no lugar */
            else if(strcmp(i.l->data.key, key) > 0)
                break;
            ant = i;
            i.l = i.l->next;
        }
        /* Se chegou aqui, é para inserir entre ant e i */
        new = (STable) malloc(sizeof(struct stable_l));
        new.l->next = i.l;
        new.l->data.key = key;
        new.l->data.data = 0;
        /* Se ant == NULL, é para inserir no começo */
        if(ant.l == NULL)
            (*table) = new;
        else
            ant.l->next = new.l;
        ret.new = 1;
        ret.data = &(new.l->data.data);
        return ret;
    }
    /* Insere no começo */
    new.l = malloc(sizeof(struct stable_l));
    new.l->next = NULL;
    new.l->data.key = key;
    new.l->data.data = 0;
    (*table) = new;
    ret.new = 1;
    ret.data = &(new.l->data.data);
    return ret;
}

STable stable_copy_lo(STable table) {
    STable i, new, j;
    if(table.l == NULL) return NULL;
    new.l = malloc(sizeof(struct stable_l));
    j = new;
    for(i = table; i.l != NULL; i.l = i.l->next) {
        j.l->data = i.l->data;
        if(i.l->next != NULL) {
            j.l->next = malloc(sizeof(struct stable_l));
            j.l = j.l->next;
        }
        else {
            j.l->next = NULL;
        }
    }
    return new;
}

void stable_sort_auxvec(sortVector v, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        stable_sort_auxvec(v, start, mid);
        stable_sort_auxvec(v, mid+1, end);
        stable_merge_auxvec(v, start, mid, end);
    }
}

STable stable_sort_lo(STable table) {
    STable i;
    sortVector v;
    int count = 0;
    for(i = table; i.l != NULL; i.l = i.l->next)
        count++;
    v.vec = (TableEntry*) malloc(count * sizeof(TableEntry));
    v.max = count;
    v.top = count;
    for(i = table, count = 0; i.l != NULL; i.l = i.l->next, count++)
        v.vec[count] = i.l->data;
    stable_sort_auxvec(v, 0, v.top - 1);
    for(i = table, count = 0; i.l != NULL; i.l = i.l->next, count++)
        i.l->data = v.vec[count];
    free(v.vec);
    return table;
}


int* stable_find_lo(STable table, const char* key) {
    STable i;
    for(i = table; i.l != NULL; i.l = i.l->next)
        if(strcmp(i.l->data.key, key) >= 0)
            break;
    if(i.l != NULL && strcmp(i.l->data.key, key) == 0)
        return &(i.l->data.data);
    return NULL;
}

void stable_destroy_lo(STable table) {
    STable i, next;
    for(i = table; i.l != NULL; i.l = next.l) {
        next.l = i.l->next;
        free(i.l);
    }
}

void stable_print_lo(STable table, const char mode) {
    STable i, copy;
    if(mode == 'A')
        for(i = table; i.l != NULL; i.l = i.l->next)
            printf("%s : %d\n", i.l->data.key, i.l->data.data);
    else {
        copy = stable_copy_lo(table);
        copy = stable_sort_lo(copy);
        for(i = copy; i.l != NULL; i.l = i.l->next)
            printf("%s : %d\n", i.l->data.key, i.l->data.data);
        stable_destroy_lo(copy);
    }
}
