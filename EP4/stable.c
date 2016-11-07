#include "stable.h"
#include <stdlib.h>
#include <stdio.h>
#include "tabelaSimbolo_AB.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"

typedef union {
    TableEntry* vector;
    struct stable_s* next;
    struct stable_s* hi, lo;
} vec_ll;

struct stable_s {
    vec_ll operator;
    TableEntry ll_data;
    int top, max;
};


STable stable_create_vector() {
    STable new;
    new = (STable) malloc(sizeof(stable_s));
    new->operator.vector = (TableEntry*) malloc(1024 * sizeof(TableEntry));
    new->top = 0;
    new->max = 1024;
    return new;
}

STable stable_create_linked_list() {
    Stable new;
    new = NULL;
    return new;
}

STable stable_create_bst() {
    Stable new;
    new = null;
    return new;
}

Result stable_insert_vector(STable table, char* type, char mode, char* key) {
    int i, mid, fim;
    Result ret;
    if(strcmp(type, "VD") == 0) {
        for(i = 0; i < table->top; i++) {
            if(strcmp(key, table->operator.vector[i].key) == 0) {
                ret.new = 0;
                ret.data = &(table->operator.vector[i].data);
                return ret;
            }
        }
        if(table->top == table->max)
            stable_reallocate_vector(table, type);
        table->operator.vector[table->top].key = key;
        table->operator.vector[table->top].data = 0;
        ret.new = 1;
        ret.data = &(table->operator.vector[table->top].data);
        return ret;
    }
    else {
        i = 0;
        fim = table->topo;
        while(i < fim) {
            mid = (table->topo)/2;


        }
        ret.new = 1;
    }
}

STable stable_create(char* type, char mode) {
    STable ret;
    if(strcmp(type, "VD") == 0 || strcmp(type, "VO") == 0) {
        ret = stable_create_vector();
    }
    else if(strcmp(type, "LD") == 0 || strcmp(type, "LO") == 0) {
        ret = stable_create_linked_list();
    }
    else if(strcmp(type, "AB") == 0) {
        ret = stable_create_bst();
    }
    else
        return NULL;
    return ret;
}

Result stable_insert(STable table, char* type, char mode, char* key) {
    Result ret;
    if(strcmp(type, "VD") == 0 || strcmp(type, "VO") == 0)
        ret = stable_insert_vector(table, type, mode, key);
    else if()
}

int* stable_find(STable table, const char* type, const char mode, char* key) {

}

void stable_destroy(STable table, char* type) {
    if(strcmp(type, "VD") == 0 || strcmp(type, "VO") == 0) {

    }
    else if(strcmp(type, "LD") == 0 || strcmp(type, "LO") == 0) {

    }
    else {

    }
}
