#ifndef __TABELASIMBOLO_AB__
#define __TABELASIMBOLO_AB__
#include "stable.h"

struct stable_s {
    TableEntry data;
    struct stable_ab* hi;
    struct stable_ab* lo;
};

STable stable_create_ab();

Result stable_insert_ab(struct stable_ab** root, char* key);

int* stable_find_ab(struct stable_ab* root, char* key);

void stable_destroy_ab(struct stable_ab* root);

void stable_print_ab(struct stable_ab* root, const char mode);

#endif
