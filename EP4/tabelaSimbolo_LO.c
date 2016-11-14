#include "stable.h"
#include "tabelaSimbolo_LO.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


STable stable_create_lo() {
    STable table;
    table.l = NULL;
    return table;
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
        new.l = malloc(sizeof(struct stable_l));
        new.l->next = i.l;
        new.l->data.key = malloc(strlen(key) * sizeof(char));
        strcpy(new.l->data.key, key);
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
    new.l->data.key = malloc(strlen(key) * sizeof(char));
    strcpy(new.l->data.key, key);
    new.l->data.data = 0;
    (*table) = new;
    ret.new = 1;
    ret.data = &(new.l->data.data);
    return ret;
}

sortVector stable_copy_lo(STable table) {
    sortVector final;
    STable i;
    int count = 0;
    for(i = table; i.l != NULL; i.l = i.l->next)
        count++;
    final.vec = malloc(count * sizeof(TableEntry));
    final.max = count;
    final.top = count;
    for(i = table, count = 0; i.l != NULL; i.l = i.l->next, count++)
        final.vec[count] = i.l->data;
    return final;
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
    STable i;
    sortVector copy;
    int a;
    if(mode == 'A')
        for(i = table; i.l != NULL; i.l = i.l->next)
            printf("%s : %d\n", i.l->data.key, i.l->data.data);
    else {
        copy = stable_copy_lo(table);
        stable_sort_auxvec_o(copy, 0, copy.top - 1);
        for(a = 0; a < copy.top; a++)
            printf("%s : %d\n", copy.vec[a].key, copy.vec[a].data);
        free(copy.vec);
    }
}
