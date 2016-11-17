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
    pos x;
    double value;
} valuedPos;

typedef struct {
    pos* v;
    int size;
} posList;

typedef struct {
    valuedPos* v;
    int top;
} valueList;

void printUsage() {
    printf("Usage: \n\t./ep5 <p/b>\n\t./ep5 <p/b> d\n");
}

posList poslist_create(int size) {
    posList new;
    new.v = malloc(size * sizeof(pos));
    new.size = size;
    return new;
}

valueList valuelist_create() {
    valueList new;
    /* Somente 196 serão usados, 4 para folga */
    new.v = malloc(200 * sizeof(valuedPos));
    new.top = 0;
    return new;
}

void valuelist_append(valueList list, valuedPos x) {
    list.v[list.top++] = x;
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

void printMove(pos aux) {
    printf("%d %d\n", aux.i, aux.j);
}

void matrix_print(matrix m) {
    int i, j;
    for(i = 0; i < 14; i++) {
        for(j = 0; j < i; j++)
            fprintf(stderr, " ");
        for(j = 0; j < 14; j++) {
            fprintf(stderr, "%c ", m[i][j].c);
        }
        fprintf(stderr, "\n");
    }
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
        aux.i = x.i - 1;
        aux.j = x.j;
        ret.v[i++] = aux;
    }
    if(x.i < 13) {
        aux.i = x.i + 1;
        aux.j = x.j;
        ret.v[i++] = aux;
    }
    if(x.j > 0) {
        aux.i = x.i;
        aux.j = x.j - 1;
        ret.v[i++] = aux;
    }
    if(x.j < 13) {
        aux.i = x.i;
        aux.j = x.j + 1;
        ret.v[i++] = aux;
    }
    if(x.i > 0 && x.j < 13) {
        aux.i = x.i - 1;
        aux.j = x.j + 1;
        ret.v[i++] = aux;
    }
    if(x.i < 13 && x.j > 0) {
        aux.i = x.i + 1;
        aux.j = x.j - 1;
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
    unsigned char i = 0, j = 0, binColor;
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
                aux.i = i;
                aux.j = 0;
                p = neighbors(aux);
            }
        }
    }
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    return 0;
}

valuedPos pointCount(matrix m, pos x, char color) {
    double posPoints = 0;
    valuedPos ret;
    ret.x = x;
    if(isFilled(m, x)) {
        ret.value = 0;
    }
    else {
        posPoints += isBridge(m, x, color);
        posPoints += isLadder(m, x, color);
        posPoints += stratPlace(m, x, color);
        posPoints += blockPath(m, x, color);
        posPoints += completeBridge(m, x, color);
        ret.value = posPoints;
    }
    return ret;
}

void takeMove(matrix m, char color) {
    int index;
    char i, j;
    pos x;
    valuedPos aux;
    valueList moves;
    moves = valuelist_create();
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            x.i = i;
            x.j = j;
            aux = pointCount(m, x, color);
            valuelist_append(moves, aux);
        }
    }
    valuelist_sort(moves);
    /* Escolhe a jogada com maior numero de pontos */
    aux = moves.v[0];
    matrix_play(m, aux.x, color);
    printMove(aux.x);
}


/*
if(print)
    matrix_print(m);
*/

int main(int argc, char **argv) {
    matrix m;
    char color;
    bool print;
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
    else {
        color = *argv[1];
        print = (argc == 3 ? 1 : 0);
    }
    return 0;
}
