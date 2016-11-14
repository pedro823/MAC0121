#include "tabelaSimbolo_AB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STable stable_create_ab() {
    return NULL;
}

Result stable_insert_ab(struct stable_ab* root, char* key) {
    Result ret;
    if(root == NULL) {
        root = malloc(sizeof(struct stable_ab));
        root->data.data = 0;
        root->data.key = key;
        ret.new = 1;
        ret.data = &(root->data.key);
        return ret;
    }
    if(strcmp(root->data.key, key) == 0) {
        ret.new = 0;
        ret.data = &(root->data.key);
        return ret;
    }
    if(strcmp(root->data.key, key) > 0) {
        /* key é maior, buscar à direita */
        return stable_insert_ab(root->hi, key);
    }
    /* key é menor, buscar à esquerda */
    return stable_insert_ab(root->lo, key);
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

void stable_print_ab(STable root, const char mode) {
    if(mode == 'A') {
        /* In-place print */
        if(root.t != NULL) {
            stable_print_ab((STable) root.t->lo, mode);
            printf("%s : %d\n", root.t->data.key, root.t->data.data);
            stable_print_ab((STable) root.t->hi, mode);
        }
    }
    else {
        /* Vector ordenation */
    }
}
