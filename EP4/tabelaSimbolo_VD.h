#ifndef __TABELASIMBOLO_VD__
#define __TABELASIMBOLO_VD__
#include "stable.h"

struct stable_s {
    TableEntry* vector;
    int max, top;
};

STable stable_create_vd();

Result stable_insert_vd(STable table, char* key);

int* stable_find_vd(STable table, char* key);

void stable_destroy_vd(STable table);

void stable_print_vd(STable table, const char mode);

#endif
