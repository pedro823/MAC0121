#include "tabelaSimbolo_LD.h"
#include "stable.h"
#include <stdio.h>

STable stable_create_ld() {
    return NULL;
}

Result stable_insert_ld(STable table, char* key) {
    Result ret;
    STable new, i;
    /* Percorre e tenta achar o elemento com key */
    if(table != NULL) {
        for(i = table; i != NULL; i = i->next) {
            if(strcmp(i->data.key, key) == 0) {
                ret.new = 0;
                ret.data = &(i->data);
                return ret;
            }
        }
    }
    /* Insere no começo */
    new = (STable) malloc(sizeof(struct stable_s));
    new->data.key = key;
    new->data.data = 0;
    new->next = table;
    table = new;
    ret.new = 1;
    ret.data = &(new->data.data);
    return ret;
}

int* stable_find_ld(STable table, char* key) {
    STable i;
    for(i = table, i != NULL; i = i->next)
        if(strcmp(i->data.key,key) == 0)
            return &(i->data.data);
    return NULL;
}
