#include "strategy.h"
#include "positionHandler.h"
#include "queue.h"
#include <stdio.h>

#ifndef bool
#define bool char
#endif

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

bool hasWon(matrix m, char color) {
    unsigned char i, j;
    pos aux, neighbor;
    queue* q;
    posList p;
    /* b = linha 0 até a 13
     * p = coluna 0 até a 13
     * LEMBRAR DE DESTRUIR POSLIST
     */
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    i = 0; j = 0;
    q = queue_create();
    if(color == 'b') {
        /* Backtracking de coluna */
        while(j < 14) {
            if(m[0][j].c == 'b' && m[0][j].visited == 0) {
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
    else {
        /* Backtracking de linha */
        /* insere todas as posições de onde a linha da
           vitória pode começar */
        while(i < 14) {
            fprintf(stderr, "m[%d][0].c = %c\n", i, m[i][0].c);
            if(m[i][0].c == 'p' && m[i][0].visited == 0) {
                fprintf(stderr, "found a piece\n");
                m[i][0].visited = 1;
                aux.i = i;
                aux.j = 0;
                p = neighbors(aux);
                queue_insertList(q, p);
                poslist_destroy(p);
            }
            i++;
        }
        fprintf(stderr, "queue_empty(*q) = %d\n", queue_empty(*q));
        /* E checa para todo vizinho delas se há um caminho */
        while(!queue_empty(*q)) {
            aux = queue_pop(q);
            fprintf(stderr, "\taux.i = %d\n\taux.j = %d\n", aux.i, aux.j);
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
    /* Se esvaziou a lista e não chegou no fim, não há
       caminho. */
    queue_destroy(q);
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    return 0;
}

int main() {
    float a;
    matrix m = matrix_create();
    char c = 'p', has;
    int i, j;
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            scanf("%*c %c", &m[i][j].c);
    matrix_print(m);
    a = judgeBoard(m, c);
    printf("%f\n", a);
    has = hasWon(m, c);
    printf("hasWon(%c): %d\n", c, has);
    has = hasWon(m, opsColor(c));
    printf("hasWon(%c): %d\n", opsColor(c), has);
    matrix_destroy(m);
    return 0;
}
