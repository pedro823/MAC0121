#ifndef __STABLE_H__
#define __STABLE_H__

typedef union {
    struct stable_v* v;
    struct stable_l* l;
    struct stable_ab* t;
} STable;

typedef enum {
    false, true
} bool;
/*
typedef union {
    int num;
    void* p;
    char* str;
} Entry;
*/
typedef struct {
    char* key;
    int data;
} TableEntry;

typedef struct {
    bool new;
    int* data;
} Result;

struct stable_l {
    TableEntry data;
    struct stable_l* next;
};

struct stable_v {
    TableEntry* vector;
    int max, top;
};

struct stable_ab {
    TableEntry data;
    struct stable_ab* lo;
    struct stable_ab* hi;
};

STable stable_create(const char* type, const char mode);

Result stable_insert(STable table, const char* type, const char mode, char* key);

int* stable_find(STable table, const char* type, const char mode, char* key);

void stable_destroy(STable table, const char* type);

void stable_print(STable table, const char* type, const char mode);

#endif
