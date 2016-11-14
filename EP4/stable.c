#include "stable.h"
#include "tabelaSimbolo_AB.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

STable stable_create(const char* type, const char mode) {
    if(strcmp(type, "VD") == 0)
        return stable_create_vd();
    else if(strcmp(type, "VO") == 0)
        return stable_create_vo();
    else if(strcmp(type, "LD") == 0)
        return stable_create_ld();
    else if(strcmp(type, "LO") == 0)
        return stable_create_lo();
    return stable_create_ab();
}

Result stable_insert(STable* table, const char* type, const char mode, char* key) {
    if(strcmp(type, "VD") == 0)
        return stable_insert_vd((*table), key);
    else if(strcmp(type, "VO") == 0)
        return stable_insert_vo((*table), key);
    else if(strcmp(type, "LD") == 0)
        return stable_insert_ld(table, key);
    else if(strcmp(type, "LO") == 0)
        return stable_insert_lo(table, key);
    return stable_insert_ab(&((*table).t), key);
}

int* stable_find(STable table, const char* type, const char mode, char* key) {
    if(strcmp(type, "VD") == 0)
        return stable_find_vd(table, key);
    else if(strcmp(type, "VO") == 0)
        return stable_find_vo(table, key);
    else if(strcmp(type, "LD") == 0)
        return stable_find_ld(table, key);
    else if(strcmp(type, "LO") == 0)
        return stable_find_lo(table, key);
    return stable_find_ab(table.t, key);
}

void stable_destroy(STable table, const char* type) {
    if(strcmp(type, "VD") == 0)
        stable_destroy_vd(table);
    else if(strcmp(type, "VO") == 0)
        stable_destroy_vo(table);
    else if(strcmp(type, "LD") == 0)
        stable_destroy_ld(table);
    else if(strcmp(type, "LO") == 0)
        stable_destroy_lo(table);
    else
        stable_destroy_ab(table.t);
}

void stable_print(STable table, const char* type, const char mode) {
    fprintf(stderr, "Entered stable_print\n");
    if(strcmp(type, "VD") == 0)
        stable_print_vd(table, mode);
    else if(strcmp(type, "VO") == 0)
        stable_print_vo(table, mode);
    else if(strcmp(type, "LD") == 0)
        stable_print_ld(table, mode);
    else if(strcmp(type, "LO") == 0)
        stable_print_lo(table, mode);
    else {
        fprintf(stderr, "ESCAPED HERE\n");
        stable_print_ab(table.t, mode);
    }
}

void stable_merge_auxvec_a(sortVector v, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0;
    sortVector aux;
    aux.vec = malloc((end - start + 1) * sizeof(TableEntry));
    while(i <= mid && j <= end) {
        if(strcmp(v.vec[i].key, v.vec[j].key) <= 0) {
            aux.vec[k++] = v.vec[i++];
        }
        else {
            aux.vec[k++] = v.vec[j++];
        }
    }
    while(i <= mid)
        aux.vec[k++] = v.vec[i++];
    while(j <= end)
        aux.vec[k++] = v.vec[j++];
    for(i = start; i <= end; i++)
        v.vec[i] = aux.vec[i - start];
    free(aux.vec);
}

void stable_merge_auxvec_o(sortVector v, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0;
    sortVector aux;
    aux.vec = malloc((end - start + 1) * sizeof(TableEntry));
    while(i <= mid && j <= end) {
        if(v.vec[i].data > v.vec[j].data) {
            aux.vec[k++] = v.vec[i++];
        }
        else
            aux.vec[k++] = v.vec[j++];
    }
    while(i <= mid)
        aux.vec[k++] = v.vec[i++];
    while(j <= end)
        aux.vec[k++] = v.vec[j++];
    for(i = start; i <= end; i++)
        v.vec[i] = aux.vec[i - start];
    free(aux.vec);
}

void stable_sort_auxvec_a(sortVector v, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        stable_sort_auxvec_a(v, start, mid);
        stable_sort_auxvec_a(v, mid+1, end);
        stable_merge_auxvec_a(v, start, mid, end);
    }
}

void stable_sort_auxvec_o(sortVector v, int start, int end) {
    int mid;
    if(start < end) {
        mid = (start + end) / 2;
        stable_sort_auxvec_o(v, start, mid);
        stable_sort_auxvec_o(v, mid+1, end);
        stable_merge_auxvec_o(v, start, mid, end);
    }
}
