#ifndef __TABELASIMBOLO_AB__
#define __TABELASIMBOLO_AB__
#include "stable.h"

struct stable_s {
    int data;
    struct stable_s* hi;
    struct stable_s* lo;
};

STable stable_create_ab();

Result stable_insert_ab(STable table, char* key);

int* stable_find_ab(STable table, char* key);

void stable_destroy_ab(STable table);

void stable_print_ab(STable table, const char mode);

#endif
