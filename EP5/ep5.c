#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define bool char

typedef struct {
    char c;
    int visited;
} matCell;

typedef matCell** matrix;


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
    printf("Usage: \n\t./ep5 <p/b>\n\t./ep5 <p/b> d\n");
}

posList poslist_create(int size) {
    posList new;
    new.v = malloc(size * sizeof(pos));
    new.size = size;
    return new;
}

matrix matrix_create() {
    matrix new;
    int i, j;
    new = malloc(14*sizeof(matCell*));
    for(i = 0; i < 14; i++)
        new[i] = malloc(14*sizeof(matCell));
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            new[i][j].c = '-';
            new[i][j].visited = 0;
        }
    }
    return new;
}

void matrix_play(matrix m, pos x, char color) {
    m[x.i][x.j].c = color;
}

void matrix_print(matrix m) {
    int i, j;
}

posList neighbors(pos x) {
    int noNeighbors = 6, i = 0;
    posList ret;
    pos aux;
    if(x.i == 0 || x.i == 13)
        noNeighbors -= 2;
    if(x.j == 0)
        noNeighbors -= (i == 13 ? 1 : 2);
    if(x.j == 13)
        noNeighbors -= (i == 0 ? 1 : 2);
    ret = poslist_create(noNeighbors);
    if(x.i > 0) {
        aux = {x.i - 1, x.j};
        ret.v[i++] = aux;
    }
    if(x.i < 13) {
        aux = {x.i + 1, x.j};
        ret.v[i++] = aux;
    }
    if(x.j > 0) {
        aux = {x.i, x.j - 1};
        ret.v[i++] = aux;
    }
    if(x.j < 13) {
        aux = {x.i, x.j + 1};
        ret.v[i++] = aux;
    }
    if(x.i > 0 && x.j < 13) {
        aux = {x.i - 1, x.j + 1};
        ret.v[i++] = aux;
    }
    if(x.i < 13 && x.j > 0) {
        aux = {x.i + 1, x.j - 1};
        ret.v[i++] = aux;
    }
    return ret;
}


char isFilled(matrix m, pos x) {
    if(m[x.i][x.j].c == 'p')
        return 1;
    if(m[x.i][x.j].c == 'b')
        return 2;
    return 0;
}

bool hasWon(matrix m, char color) {
    char i = 0, j = 0, binColor;
    pos aux;
    stack s;
    posList p;
    /* b = linha 0 até a 13
       p = coluna 0 até a 13 */
    if(color == 'p') {
        /* Backtracking de coluna */

    }
    else {
        /* Backtracking de linha */
        while(i < 13) {
            if(m[i][0].visited == 0) {
                p = neighbors(i, 0);

            }
        }
    }
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    return 0;
}

valuedPos pointCount(pos x) {

}

int main(int argc, char **argv) {
    matrix m;
    char color;
    /* Verifications */
    if(argc < 2 || argc > 3) {
        printUsage();
        return -1;
    }
    else if(strcmp(argv[1], "p") && strcmp(argv[1], "b")) {
        printUsage();
        return -1;
    }
    else if(argc == 3 && strcmp(argv[2], "d") != 0) {
        printUsage();
        return -1;
    }
    else
        color = *argv[1];

    return 0;
}
