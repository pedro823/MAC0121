#include "stable.h"
#include <stdlib.h>
#include <stdio.h>

struct stable_s {
    char** vector;
    int topo;
};

STable stable_create_vector() {
    STable new;
    new->vector = (char**) malloc(1024 * sizeof(char*));
    new->topo = 0;
    return new;
}

STable stable_create(char* type, char mode) {
    STable ret;
    if(strcmp(type, "VD") == 0 || strcmp(type, "VO") == 0) {
        ret = stable_create_vector();
    }
    else if(strcmp(type, "LD") == 0) {

    }
    else if(strcmp(type, "LO") == 0) {

    }
    else if(strcmp(type, "AB") == 0) {

    }
    return NULL;
}

Result stable_insert(char* type, char mode, char* key) {

}

void stable_destroy(STable table, char* type) {

}
