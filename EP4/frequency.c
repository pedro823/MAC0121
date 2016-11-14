#include <stdio.h>
#include "stable.h"
#include <stdlib.h>
#include "buffer.h"
#include <ctype.h>

void printUsage() {
    printf("Usage: ./EP4 <file> <type> <mode>\n");
}


int main(int argAmount, char **argv) {
    char* type;
    char c, mode;
    STable table;
    Buffer* buffer;
    Result ret;
    FILE* f;
    if(argAmount != 4) {
        printUsage();
        return -1;
    }
    f = fopen(argv[1], "r");
    if(f == NULL) {
        printf("Error: ep4: Invalid file\n");
        return -1;
    }
    type = argv[2];
    mode = *(argv[3]);
    table = stable_create(type, mode);
    buffer = buffer_create();
    c = fgetc(f);
    while(c != EOF) {
        while(isalnum(c)) {
            buffer_push_back(buffer, tolower(c));
            c = fgetc(f);
        }
        ret = stable_insert(&table, type, mode, buffer->data);
        if(ret.new) {
            *ret.data = 1;
        }
        else {
            (*ret.data)++;
        }
        buffer_reset(buffer);
        while(!isalnum(c) && c != EOF) {
            c = fgetc(f);
        }
    }
    stable_print(table, type, mode);
    fclose(f);
    buffer_destroy(buffer);
    stable_destroy(table, type);
    return 0;
}
