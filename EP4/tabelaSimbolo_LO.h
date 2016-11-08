#ifndef __TABELASIMBOLO_LO__
#define __TABELASIMBOLO_LO__
#include "stable.h"

STable stable_create_lo();

Result stable_insert_lo(STable* table, char* key);

int* stable_find_lo(STable table, const char* key);

void stable_destroy_lo(STable table);

void stable_print_lo(STable table, const char mode);

#endif
