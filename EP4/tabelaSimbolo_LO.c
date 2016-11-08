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
        while(i != NULL) {
            if(strcmp(i->data.key, key) == 0) {
                ret.new = 0;
                ret.data = &(i->data.data);
                return ret;
            }
            /* Inserir no lugar */
            else if(strcmp(i->data.key, key) > 0)
                break;
            ant = i;
            i = i->next;
        }
        /* Se chegou aqui, é para inserir entre ant e i */
        new = (STable) malloc(sizeof(struct stable_s));
        new->next = i;
        new->data.key = key;
        new->data.data = 0;
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
    new->next = NULL;
    new->data.key = key;
    new->data.data = 0;
    (*table) = new;
    ret.new = 1;
    ret.data = &(new->data.data);
    return ret;
}

int* stable_find_lo(STable table, const char* key) {
    STable i;
    for(i = table; i != NULL && strcmp(i->data.key, key) < 0; i = i->next);
    if(i != NULL && strcmp(i->data.key, key) == 0)
        return &(i->data.data);
    return NULL;
}

void stable_destroy_lo(STable table) {
    STable i, next;
}
