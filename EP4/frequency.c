#include <stdio.h>
#include "stable.h"
#include <stdlib.h>

void printUsage() {
    printf("Usage: ./EP4 <file> <type> <mode>\n");
}

void printError(int errno) {
    if(errno == 0)
        printf("ERROR: EP4: invalid file");
    else if(errno == 1)

}

int main(int argAmount, int **argv) {
    char* type, file;
    char mode;
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

    return 0;
}
