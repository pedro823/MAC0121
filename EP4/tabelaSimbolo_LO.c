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
    if((*table) != NULL) {
        i = (*table);
        ant = NULL;
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
            i = i.l->next;
        }
        /* Se chegou aqui, é para inserir entre ant e i */
        new = (STable) malloc(sizeof(struct stable_s));
        new.l->next = i;
        new.l->data.key = key;
        new.l->data.data = 0;
        /* Se ant == NULL, é para inserir no começo */
        if(ant == NULL)
            (*table) = new;
        else
            ant->next = new;
        ret.new = 1;
        ret.data = &(new->data.data);
        return ret;
    }
    /* Insere no começo */
    new = (STable) malloc(sizeof(struct stable_s));
    new.l->next = NULL;
    new.l->data.key = key;
    new.l->data.data = 0;
    (*table) = new;
    ret.new = 1;
    ret.data = &(new.l->data.data);
    return ret;
}

int* stable_find_lo(STable table, const char* key) {
    STable i;
    for(i = table; i.l != NULL && strcmp(i.l->data.key, key) < 0; i = i.l->next);
    if(i.l != NULL && strcmp(i.l->data.key, key) == 0)
        return &(i.l->data.data);
    return NULL;
}

void stable_destroy_lo(STable table) {
    STable i, next;
    for(i = table; i != NULL; i = next) {
        next = i.l->next;
        free(i);
    }
}

void stable_print_lo(STable table, const char mode) {
    STable i;
    if(mode == 'A')
        for(i = table; i != NULL; i = i.l->next)
            printf("%s : %d\n", i.l->data.key, i.l->data.data);
    else {

    }
}
