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
    for(i = table; i != NULL; i = i->next)
        if(strcmp(i.l->data.key,key) == 0)
            return &(i.l->data.data);
    return NULL;
}

void stable_destroy_ld(STable table) {

}

void stable_print_ld(STable table, const char mode) {

}
