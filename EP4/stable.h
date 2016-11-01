#ifndef __STABLE_H__
#define __STABLE_H__

typedef struct stable_s* STable;

typedef enum {
    false, true
} bool;

typedef union {
    int num;
    void* p;
    char* str;
} Entry;

typedef struct {
    char* key;
    Entry data;
} TableEntry;

typedef struct {
    bool new;
    int* data;
} Result;

STable stable_create(const char* type, const char mode);

Result stable_insert(STable table, char* type, char mode, char* key);

Entry stable_find(STable table, const char* type, const char mode, char* key);

void stable_destroy(STable table, char* type);

#endif
