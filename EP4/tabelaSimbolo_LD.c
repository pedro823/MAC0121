#include "tabelaSimbolo_LD.h"
#include "stable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_ld() {
    return NULL;
}

Result stable_insert_ld(STable* table, char* key) {
    Result ret;
    STable new, i;
    /* Percorre e tenta achar o elemento com key */
    if((*table) != NULL) {
        for(i = (*table); i != NULL; i = i->next) {
            if(strcmp(i->data.key, key) == 0) {
                ret.new = 0;
                ret.data = &(i->data.data);
                return ret;
            }
        }
    }
    /* Insere no começo */
    new = (STable) malloc(sizeof(struct stable_l));
    new.l->data.key = key;
    new.l->data.data = 0;
    new.l->next = (*table);
    (*table) = new;
    ret.new = 1;
    ret.data = &(new.l->data.data);
    return ret;
}

int* stable_find_ld(STable table, char* key) {
    STable i;
    for(i = table; i != NULL; i = i.l->next)
        if(strcmp(i.l->data.key,key) == 0)
            return &(i.l->data.data);
    return NULL;
}

void stable_sort_print_a(STable table) {
    STable i;
    sortVector v;
    int count = 0;
    for(i = table; i != NULL; i = i.l->next)
        count++;
    v.vec = (TableEntry*) malloc(count * sizeof(TableEntry));
    v.max = count;
    v.top = count;
    for(i = table, count = 0; i != NULL; i = i.l->next, count++)
        v.vec[count] = i.l->data;
    stable_sort_auxvec_a(v, 0, v.top - 1);
    for(count = 0; count < v.top; count++)
        printf("%s : %d\n", v.vec[count]->key, v.vec[count]->data);
    free(v.vec);
}

void stable_sort_print_o(STable table) {
    STable i;
    sortVector v;
    int count = 0;
    for(i = table; i != NULL; i = i.l->next)
        count++;
    v.vec = (TableEntry*) malloc(count * sizeof(TableEntry));
    v.max = count;
    v.top = count;
    for(i = table, count = 0; i != NULL; i = i.l->next, count++)
        v.vec[count] = i.l->data;
    stable_sort_auxvec_o(v, 0, v.top - 1);
    for(count = 0; count < v.top; count++)
        printf("%s : %d\n", v.vec[count]->key, v.vec[count]->data);
    free(v.vec);
}

STable stable_copy_ld(STable table) {
    STable i, new, j;
    if(table == NULL) return NULL;
    new = (STable) malloc(sizeof(struct stable_l));
    j = new;
    for(i = table; i != NULL; i = i.l->next) {
        j.l->data = i.l->data;
        if(i.l->next != NULL) {
            j.l->next = (STable) malloc(sizeof(struct stable_l));
            j = j.l->next;
        }
        else {
            j.l->next = NULL;
        }
    }
    return new;
}


void stable_destroy_ld(STable table) {
    STable i, next;
    for(i = table; i != NULL; i = next) {
        next = i.l->next;
        free(i);
    }
}

void stable_print_ld(STable table, const char mode) {
    STable copy;
    copy = stable_copy_ld(table);
    if(mode == 'A') {
        stable_sort_print_a(copy);
    }
    else {
        stable_sort_print_o(copy);
    }
}
