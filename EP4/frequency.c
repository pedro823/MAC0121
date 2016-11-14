#include <stdio.h>
#include "stable.h"
#include <stdlib.h>
#include "buffer.h"
#include <ctype.h>

void printUsage() {
    printf("Usage: ./EP4 <file> <type> <mode>\n");
}

void printError(int errno) {
    if(errno == 0)
        printf("ERROR: EP4: invalid file");

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
        printError(0);
        return -1;
    }
    fprintf(stderr, "Opened file\n");
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
        fprintf(stderr, "Read word: %s\n", buffer->data);
        ret = stable_insert(&table, type, mode, buffer->data);
        fprintf(stderr, "Inserted onto stable\n");
        if(ret.new) {
            *ret.data = 1;
            fprintf(stderr, "\tNew word!\n");
        }
        else {
            (*ret.data)++;
            fprintf(stderr, "\told word. *ret.data = %d\n", *ret.data);
        }
        buffer_reset(buffer);
        while(!isalnum(c) && c != EOF) {
            c = fgetc(f);
        }
        fprintf(stderr, "loop\n");
    }
    stable_print(table, type, mode);
    fprintf(stderr, "Out of the loop\n");
    fclose(f);
    fprintf(stderr, "Closed file\n");
    buffer_destroy(buffer);
    fprintf(stderr, "Destroyed buffer\n");
    stable_destroy(table, type);
    fprintf(stderr, "Destroyed table\n");
    return 0;
}
