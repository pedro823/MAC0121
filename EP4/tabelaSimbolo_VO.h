#ifndef __TABELASIMBOLO_VO__
#define __TABELASIMBOLO_VO__
#include "stable.h"

struct stable_s {
    TableEntry* vector;
    int max, top;
};

STable stable_create_vo();

Result stable_insert_vo(STable table, char* key);

int* stable_find_vo(STable table, char* key);

void stable_destroy_vo(STable table);

void stable_print_vo(STable table, const char mode);

#endif
