#include <stdio.h>
#include "stable.h"
#include <stdlib.h>

void printUsage() {
    printf("Usage: ./EP4 <file> <type> <mode>\n");
}

int main(int argAmount, int **argv) {
    char* type, file;
    char mode;

    if(argAmount != 4) {
        printUsage();
        return 0;
    }

    return 0;
}
