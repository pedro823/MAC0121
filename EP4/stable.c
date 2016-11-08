#include "stable.h"
#include "tabelaSimbolo_AB.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"
#include <string.h>

STable stable_create(const char* type, const char mode) {
    if(strcmp(type, "VD") == 0)
        stable_create_vd();
    else if(strcmp(type, "VO") == 0)
        stable_create_vo();
    else if(strcmp(type, "LD") == 0)
        stable_create_ld();
    else if(strcmp(type, "LO") == 0)
        stable_create_lo();
    stable_create_ab();
}

Result stable_insert(STable table, const char* type, const char mode, char* key) {
    if(strcmp(type, "VD") == 0)
        return stable_insert_vd(table, key);
    else if(strcmp(type, "VO") == 0)
        return stable_insert_vo(table, key);
    else if(strcmp(type, "LD") == 0)
        return stable_insert_ld(table, key);
    else if(strcmp(type, "LO") == 0)
        return stable_insert_lo(table, key);
    return stable_insert_ab(table, key);
}

int* stable_find(STable, const char* type, const char mode, char*key) {
    if(strcmp(type, "VD") == 0)
        return stable_find_vd(table, key);
    else if(strcmp(type, "VO") == 0)
        return stable_find_vo(table, key);
    else if(strcmp(type, "LD") == 0)
        return stable_find_ld(table, key);
    else if(strcmp(type, "LO") == 0)
        return stable_find_lo(table, key);
    return stable_find_ab(table, key);
}

void stable_destroy(STable table, const char* type) {
    if(strcmp(type, "VD") == 0)
        stable_destroy_vd(table);
    else if(strcmp(type, "VO") == 0)
        stable_destroy_vo(table);
    else if(strcmp(type, "LD") == 0)
        stable_destroy_ld(table);
    else if(strcmp(type, "LO") == 0)
        stable_destroy_lo(table);
    stable_destroy_ab(table);
}

void stable_print(STable table, const char* type, const char mode) {
    if(strcmp(type, "VD") == 0)
        stable_print_vd(table, mode);
    else if(strcmp(type, "VO") == 0)
        stable_print_vo(table, mode);
    else if(strcmp(type, "LD") == 0)
        stable_print_ld(table, mode);
    else if(strcmp(type, "LO") == 0)
        stable_print_lo(table, mode);
    stable_print_ab(table, mode);
}
