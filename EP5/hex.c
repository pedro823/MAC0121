#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "positionHandler.h"
#include "strategy.h"

#define bool char

/* Protótipo dessa função para poder usar no pruneMax */
float alphaBetaPruneMin(matrix m, float a, float b, int depth, char color);

void printUsage() {
    printf("Usage: \n\t./ep5 <p/b>\n\t./ep5 <p/b> d\n");
}

void matrix_play(matrix m, pos x, char color) {
    m[x.i][x.j].c = color;
}

void printMove(pos aux) {
    printf("%d %d\n", aux.i, aux.j);
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
    pos aux, neighbor;
    queue* q;
    posList p;
    /* b = linha 0 até a 13
     * p = coluna 0 até a 13
     * LEMBRAR DE DESTRUIR POSLIST
     */
     q = queue_create();
    if(color == 'p') {
        /* Backtracking de coluna */
        while(j < 13) {
            if(m[0][j].c == 'p' && m[0][j].visited == 0) {
                m[0][j].visited = 1;
                aux.i = 0;
                aux.j = j;
                p = neighbors(aux);
                queue_insertList(q, p);
                poslist_destroy(p);
            }
            j++;
        }
        while(!queue_empty(*q)) {
            aux = queue_pop(q);
            if(aux.i == 13) {
                queue_destroy(q);
                for(i = 0; i < 14; i++)
                    for(j = 0; j < 14; j++)
                        m[i][j].visited = 0;
                return 1;
            }
            p = neighbors(aux);
            for(j = 0; j < p.size; j++) {
                neighbor = p.v[j];
                if(m[neighbor.i][neighbor.j].c == 'p') {
                    if(m[neighbor.i][neighbor.j].visited == 0) {
                        m[neighbor.i][neighbor.j].visited = 1;
                        queue_insert(q, neighbor);
                    }
                }
            }
            poslist_destroy(p);
        }
    }
    else {
        /* Backtracking de linha */
        /* insere todas as posições de onde a linha da
           vitória pode começar */
        while(i < 13) {
            if(m[i][0].c == 'b' && m[i][0].visited == 0) {
                m[i][0].visited = 1;
                aux.i = i;
                aux.j = 0;
                p = neighbors(aux);
                queue_insertList(q, p);
                poslist_destroy(p);
            }
            i++;
        }
        /* E checa para todo vizinho delas se há um caminho */
        while(!queue_empty(*q)) {
            aux = queue_pop(q);
            if(aux.j == 13) {
                /* Chegou em uma peça que toca no outro lado
                   do tabuleiro: vitória! */
                queue_destroy(q);
                for(i = 0; i < 14; i++)
                    for(j = 0; j < 14; j++)
                        m[i][j].visited = 0;
                return 1;
            }
            p = neighbors(aux);
            for(j = 0; j < p.size; j++) {
                neighbor = p.v[j];
                if(m[neighbor.i][neighbor.j].c == 'b') {
                    if(m[neighbor.i][neighbor.j].visited == 0) {
                        m[neighbor.i][neighbor.j].visited = 1;
                        queue_insert(q, neighbor);
                    }
                }
            }
            poslist_destroy(p);
        }
    }
    /* Se esvaziou a lista e não chegou no fim, não há
       caminho. */
    queue_destroy(q);
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    return 0;
}

float alphaBetaPruneMax(matrix m, float a, float b, int depth, char color) {
    unsigned char i, j;
    float score;
    if(depth == 0) return judgeBoard(m, color);
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            if(m[i][j].c == '-') {
                score = alphaBetaPruneMin(m, a, b, depth - 1, color);
                if(score >= b)
                    return b; /* Poda a árvore por beta */
                if(score > a)
                    a = score; /* Maximizador para o jogador da vez */
            }
        }
    }
    return a;
}

float alphaBetaPruneMin(matrix m, float a, float b, int depth, char color) {
    unsigned char i, j;
    float score;
    if(depth == 0) return -judgeBoard(m, color);
    for(i = 0; i < 14; i++) {
        for (j = 0; j < 14; j++) {
            if(m[i][j].c == '-') {
                score = alphaBetaPruneMax(m, a, b, depth - 1, color);
                if(score <= a)
                    return a; /* Poda a arvore por alpha */
                if(score > b)
                    b = score; /* Minimizador para o jogador adversário */
            }
        }
    }
    return b;
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
