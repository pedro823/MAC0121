#ifndef __TABELASIMBOLO_LD__
#define __TABELASIMBOLO_LD__
#include "stable.h"


STable stable_create_ld();

Result stable_insert_ld(STable* table, char* key);

int* stable_find_ld(STable table, char* key);

void stable_destroy_ld(STable table);

void stable_print_ld(STable table, const char mode);

#endif
