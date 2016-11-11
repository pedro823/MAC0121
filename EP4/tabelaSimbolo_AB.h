#ifndef __TABELASIMBOLO_AB__
#define __TABELASIMBOLO_AB__
#include "stable.h"

struct stable_s {
    TableEntry data;
    struct stable_ab* hi;
    struct stable_ab* lo;
};

STable stable_create_ab();

Result stable_insert_ab(STable root, char* key);

int* stable_find_ab(STable root, char* key);

void stable_destroy_ab(STable root);

void stable_print_ab(STable root, const char mode);

#endif