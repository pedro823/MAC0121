#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define bool char

typedef char** matrix;


typedef struct {
    char i, j;
    double value;
} valuedPos;

typedef struct {
    pos* v;
    int size;
} posList;

typedef valuedPos* valueList;

void printUsage() {
    printf("Usage: ./ep5 <p/b>");
}

matrix matrix_create() {
    matrix new;
    int i, j;
    new = malloc(14*sizeof(char*));
    for(i = 0; i < 14; i++)
        new[i] = malloc(14*sizeof(char));
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            new[i][j] = '-';
    return new;
}

posList neighbors(pos x) {

}


char isFilled(matrix m, pos x) {
    if(m[x.i][x.j] == 'p')
        return 1;
    if(m[x.i][x.j] == 'b')
        return 2;
    return 0;
}

bool hasWon(matrix m, char color) {
    char i, j, binColor;
    posList p;
    if(color == 'p') {

    }
    else {

    }
}

valuedPos pointCount(pos x) {

}

int main(int argc, char **argv) {
    matrix m;
    char color;
    /* Verifications */
    if(argc != 2) {
        printUsage();
        return -1;
    }
    else if(strcmp(argv[1], "p") && strcmp(argv[1], "b")) {
        printUsage();
        return -1;
    }
    else
        color = *argv[1];

    return 0;
}
