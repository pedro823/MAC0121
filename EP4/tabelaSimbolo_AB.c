#include "tabelaSimbolo_AB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_ab() {
    STable table;
    table.t = NULL;
    return table;
}

Result stable_insert_ab(struct stable_ab** root, char* key) {
    Result ret;
    if(*root == NULL) {
        *root = malloc(sizeof(struct stable_ab));
        (*root)->data.data = 0;
        (*root)->data.key = malloc(strlen(key) * sizeof(char));
        strcpy((*root)->data.key, key);
        ret.new = 1;
        ret.data = &((*root)->data.data);
        return ret;
    }
    if(strcmp((*root)->data.key, key) == 0) {
        ret.new = 0;
        ret.data = &((*root)->data.data);
        return ret;
    }
    if(strcmp((*root)->data.key, key) > 0) {
        /* key é maior, buscar à direita */
        return stable_insert_ab(&((*root)->hi), key);
    }
    /* key é menor, buscar à esquerda */
    return stable_insert_ab(&((*root)->lo), key);
}

int stable_count_ab(struct stable_ab* root) {
    if(root == NULL)
        return 0;
    return 1 + stable_count_ab(root->lo) + stable_count_ab(root->hi);
}

void stable_copy_ab(struct stable_ab* root, sortVector* v) {
    if(root != NULL) {
        stable_copy_ab(root->lo, v);
        v->vec[v->top++] = root->data;
        stable_copy_ab(root->hi, v);
    }
}

int* stable_find_ab(struct stable_ab* root, char* key) {
    if(root == NULL)
        return NULL;
    if(strcmp(root->data.key, key) == 0)
        return &(root->data.data);
    if(strcmp(root->data.key, key) > 0)
        return stable_find_ab(root->hi, key);
    return stable_find_ab(root->lo, key);
}

void stable_destroy_ab(struct stable_ab* root) {
    /* Destroi esq, destroi dir, destroi raiz */
    if(root != NULL) {
        stable_destroy_ab(root->lo);
        stable_destroy_ab(root->hi);
        free(root);
    }
}

void stable_print_ab(struct stable_ab* root, const char mode) {
    sortVector v;
    int i;
    if(mode == 'A') {
        /* Reversed in-place print */
        if(root != NULL) {
            stable_print_ab(root->hi, mode);
            printf("%s : %d\n", root->data.key, root->data.data);
            stable_print_ab(root->lo, mode);
        }
    }
    else {
        /* Vector ordenation */
        i = stable_count_ab(root);
        v.vec = malloc(i * sizeof(TableEntry));
        v.top = 0;
        v.max = i;
        stable_copy_ab(root, &v);
        stable_sort_auxvec_o(v, 0, v.top - 1);
        for(i = 0; i < v.top; i++)
            printf("%s : %d\n", v.vec[i].key, v.vec[i].data);
    }
}
