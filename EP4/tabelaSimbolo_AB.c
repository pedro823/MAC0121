#include "tabelaSimbolo_AB.h"

STable stable_create_ab() {
    return NULL;
}

Result stable_insert_ab(STable root, char* key) {
    Result ret;
    if(root.t == NULL) {
        root = (STable) malloc(sizeof(struct stable_ab));
        root.t->data.data = 0;
        root.t->data.key = key;
        ret.new = 1;
        ret.data = &(root.t->data.key);
        return ret;
    }
    if(strcmp(root.t->data.key, key) == 0) {
        ret.new = 0;
        ret.data = &(root.t->data.key);
        return ret;
    }
    if(strcmp(root.t->data.key, key) > 0) {
        /* key é maior, buscar à direita */
        return stable_insert_ab(root.t->hi, key);
    }
    /* key é menor, buscar à esquerda */
    return stable_insert_ab(root.t->lo, key);
}

int* stable_find_ab(STable root, char* key) {
    if(root.t == NULL)
        return NULL;
    if(strcmp(root.t->data.key, key) == 0)
        return &(root.t->data.data);
    if(strcmp(root.t->data.key, key) > 0)
        return stable_insert_ab(root.t->hi, key);
    return stable_insert_ab(root.t->lo, key);
}

void stable_destroy_ab(STable root);
    /* Destroi esq, destroi dir, destroi raiz */
    if(root != NULL) {
        stable_destroy_ab(root.t->lo);
        stable_destroy_ab(root.t->hi);
        free(root);
    }
}

void stable_print_ab(STable root, const char mode) {
    if(mode == 'A') {
        /* In-place print */
        if(root.t != NULL) {
            stable_print_ab(root.t->lo, mode);
            printf("%s : %d\n", root.t->data.key, root.t->data.data);
            stable_print_ab(root.t->hi, mode);
        }
    }
    else {
        /* Vector ordenation */
    }
}
