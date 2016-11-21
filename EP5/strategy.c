#include "positionHandler.h"
#include "strategy.h"
#include <stdio.h>

#define negInf -1000000
#define posInf  1000000

/* Mapeado à mão e melhorado depois de jogos */
static const float BlackStrategy[14][14] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0.0078125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0.003125, 0, 0, 0.25, 0, 0, 0.25, 0.25, 0, 0, 0, 0},
    {0, 0, 0, 0.125, 0, 0, 0, 0, 0, 0, 0.125, 0, 0, 0},
    {0, 0, 0, 0, 0.5, 0, 0, 0.6667, 0.6667, 0, 0, 0, 0, 0},
    {0, 0, 0.25, 0, 0, 0.6667, 0, 0, 0, 0.5, 0, 0, 0, 0},
    {0, 0, 0, 0.5, 0, 0, 1, 1, 0, 0.5, 0, 0, 0, 0},
    {0, 0, 0, 0, 0.5, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0.25, 0, 0.5, 0, 0, 0, 0.6667, 0, 0, 0, 0, 0},
    {0, 0, 0.25, 0, 0, 0.6667, 0.6667, 0, 0, 0.5, 0, 0, 0, 0},
    {0, 0, 0, 0.125, 0, 0, 0, 0.5, 0, 0, 0.125, 0, 0, 0},
    {0, 0, 0, 0, 0.25, 0.25, 0, 0, 0.25, 0, 0, 0.003125, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0078125, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const float WhiteStrategy[14][14] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0.0078125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0.03125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0.125, 0, 0, 0, 0, 0, 0, 0.125, 0, 0, 0},
    {0, 0, 0, 0, 0.5, 0, 0, 0.5, 0.5, 0, 0, 0.25, 0, 0},
    {0, 0, 0.25, 0, 0, 0.6667, 0, 0, 0, 0.6667, 0, 0.25, 0, 0},
    {0, 0, 0, 0.5, 0, 0, 1, 1, 0, 0.6667, 0, 0, 0, 0},
    {0, 0, 0, 0, 0.6667, 0, 1, 1, 0, 0, 0.5, 0, 0, 0},
    {0, 0, 0.25, 0, 0.6667, 0, 0, 0, 0.6667, 0, 0, 0.25, 0, 0},
    {0, 0, 0.25, 0, 0, 0.5, 0.5, 0, 0, 0.5, 0, 0, 0, 0},
    {0, 0, 0, 0.125, 0, 0, 0, 0, 0, 0, 0.125, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.03125, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0078125, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static const float BlackInfluence[14][14] = {
    {0.05, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.01},
    {0.05, 0.1, 0.3, 0.3, 0.3, 0.3, 0.3, 0.5, 0.5, 0.5, 0.5, 0.4, 0.2, 0.05},
    {0.05, 0.1, 0.3, 0.3, 0.4, 0.4, 0.4, 0.4, 0.6, 0.6, 0.4, 0.2, 0.2, 0.05},
    {0.05, 0.1, 0.15, 0.3, 0.3, 0.3, 0.8, 0.8, 0.8, 0.8, 0.3, 0.2, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.3, 0.6, 0.6, 0.6, 0.9, 0.9, 0.6, 0.4, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.3, 0.6, 1, 1, 1, 1, 0.5, 0.4, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.4, 0.6, 1, 1.2, 1.2, 1, 0.5, 0.4, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.4, 0.5, 1, 1.2, 1.2, 1, 0.6, 0.4, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.4, 0.5, 1, 1, 1, 1, 0.6, 0.3, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.15, 0.4, 0.6, 0.9, 0.9, 0.6, 0.6, 0.6, 0.3, 0.15, 0.1, 0.05},
    {0.05, 0.1, 0.2, 0.3, 0.8, 0.8, 0.8, 0.8, 0.3, 0.3, 0.3, 0.15, 0.1, 0.05},
    {0.05, 0.2, 0.2, 0.4, 0.6, 0.6, 0.4, 0.4, 0.4, 0.4, 0.3, 0.3, 0.1, 0.05},
    {0.05, 0.2, 0.4, 0.5, 0.5, 0.5, 0.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.1, 0.05},
    {0.01, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.05},
};

static const float WhiteInfluence[14][14] = {
    {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.01},
    {0.5, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2, 0.5},
    {0.5, 0.3, 0.3, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.2, 0.2, 0.4, 0.5},
    {0.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.4, 0.5, 0.5},
    {0.5, 0.3, 0.4, 0.3, 0.6, 0.6, 0.6, 0.5, 0.5, 0.6, 0.8, 0.6, 0.5, 0.5},
    {0.5, 0.3, 0.4, 0.3, 0.6, 1, 1, 1, 1, 0.9, 0.8, 0.6, 0.5, 0.5},
    {0.5, 0.3, 0.4, 0.8, 0.6, 1, 1.2, 1.2, 1, 0.9, 0.8, 0.4, 0.5, 0.5},
    {0.5, 0.5, 0.4, 0.8, 0.9, 1, 1.2, 1.2, 1, 0.6, 0.8, 0.4, 0.3, 0.5},
    {0.5, 0.5, 0.6, 0.8, 0.9, 1, 1, 1, 1, 0.6, 0.3, 0.4, 0.3, 0.5},
    {0.5, 0.5, 0.6, 0.8, 0.6, 0.5, 0.5, 0.6, 0.6, 0.6, 0.3, 0.4, 0.3, 0.5},
    {0.5, 0.5, 0.4, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.3, 0.3, 0.3, 0.3, 0.5},
    {0.5, 0.4, 0.2, 0.2, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.3, 0.3, 0.5},
    {0.5, 0.2, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.5},
    {0.01, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
};

/* Tunado à mão depois de vários jogos. */

/* Multiplicador da influencia das pontes */
static const float BridgeMult = 4;
/* Multiplicador do dano causado por não completar
   uma ponte */
static const float Uncomplete = -2.5;
static const float CompleteBridge = 0.5;
static const float VirtualBridge = 0.3;
/* Multiplicador das posições vantajosas */
static const float StratMult = 1;
/* Multiplicadores de longas cadeias */
static const float ChainMult = 1;
static const float ChainBase = 1.11;


/* Põe em uma posList todos os vizinhos de x */
posList ListAllNeighbors(pos x) {
    posList ret;
    pos aux;
    ret = poslist_create(12);
    if(x.i >= 1) {
        aux.i = x.i - 1;
        aux.j = x.j;
        ret.v[ret.top++] = aux;
        if(x.j < 13) {
            aux.j = x.j + 1;
            ret.v[ret.top++] = aux;
            if(x.j < 12) {
                aux.j = x.j + 2;
                ret.v[ret.top++] = aux;
            }
            if(x.i >= 2) {
                aux.i = x.i - 2;
                aux.j = x.j + 1;
                ret.v[ret.top++] = aux;
            }
        }
        if(x.j >= 1) {
            aux.j = x.j - 1;
            ret.v[ret.top++] = aux;
        }
    }
    if(x.j >= 1) {
        aux.i = x.i;
        aux.j = x.j - 1;
        ret.v[ret.top++] = aux;
    }
    if(x.j < 13) {
        aux.i = x.i;
        aux.j = x.j + 1;
        ret.v[ret.top++] = aux;
    }
    if(x.i < 13) {
        aux.i = x.i + 1;
        aux.j = x.j;
        ret.v[ret.top++] = aux;
        if(x.j < 13) {
            aux.j = x.j + 1;
            ret.v[ret.top++] = aux;
        }
        if(x.j >= 1) {
            aux.j = x.j - 1;
            ret.v[ret.top++] = aux;
            if(x.j >= 2) {
                aux.j = x.j - 2;
                ret.v[ret.top++] = aux;
            }
            if(x.i < 12) {
                aux.i = x.i + 2;
                aux.j = x.j - 1;
                ret.v[ret.top++] = aux;
            }
        }

    }
    return ret;
}

/* Exponenciação em O(log n) */
float fastpow(float base, int expo) {
    float ans;
    if(expo <= 0)
        ans = 1;
    while(expo > 0) {
        if(expo % 2)
            ans *= base;
        base *= base;
        expo >>= 1;
    }
    return ans;
}

float correctBounds(float n) {
    if(n > posInf)
    n = posInf;
    if(n < negInf)
    n = negInf;
    return n;
}

/* Retorna a cor oposta */
char opsColor(char color) {
    return color == 'p' ? 'b' : 'p';
}

float bridge(matrix m, pos x, char color) {
    /* Analisar os vizinhos de ponte de x
     * Devolver pontos positivos se há uma ponte fazível
     * Devolver pontos positivos se a ponte já está feita
     * Devolver muitos pontos negativos se a ponte tem
        uma peça no meio da ponte */
    float result;
    if(m[x.i][x.j].c == color) {
        /* Sentido horario */
        if(x.i >= 2 && x.j <= 12 && m[x.i - 2][x.j + 1].c == color) {
            if(m[x.i - 1][x.j].c == color || m[x.i - 1][x.j + 1].c == color) {
                if(color == 'p')
                    result += BlackInfluence[x.i][x.j] * CompleteBridge;
                else
                    result += WhiteInfluence[x.i][x.j] * CompleteBridge;
            }
            else if(m[x.i - 1][x.j].c == opsColor(color)
                || m[x.i - 1][x.j + 1].c == opsColor(color)) {
                if(color == 'p')
                    result += BlackInfluence[x.i][x.j] * Uncomplete;
                else
                    result += WhiteInfluence[x.i][x.j] * Uncomplete;
            }
            else {
                if(color == 'p')
                    result += BlackInfluence[x.i][x.j] * VirtualBridge;
                else
                    result += WhiteInfluence[x.i][x.j] * VirtualBridge;
            }
        }
    }
    else {
        result = 0;
    }
    return correctBounds(result * BridgeMult);
}

float bridgeFunction(matrix m, char color) {
    float ans = 0;
    pos aux;
    unsigned char i, j;
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            aux.i = i;
            aux.j = j;
            ans += bridge(m, aux, color);
        }
    }
    return ans;
}

int partialDfs(matrix m, pos x, char color, int value) {
    int i, amount = 1;
    pos aux;
    posList p = ListAllNeighbors(x);
    fprintf(stderr, "partialDfs:\n");
    m[x.i][x.j].visited = value;
    for(i = 0; i < p.top; i++) {
        aux = p.v[i];
        if(m[aux.i][aux.j].c == color) {
            if(m[aux.i][aux.j].visited == 0) {
                m[aux.i][aux.j].visited = value;
                amount += partialDfs(m, aux, color, value);
            }
        }
    }
    poslist_destroy(p);
    return amount;
}


float dfsbridge(matrix m, char color) {
    unsigned char i, j;
    int count = 1, largest = 0, chain;
    float result;
    pos x;
    fprintf(stderr, "dfsbridge:\n");
    for(i = 0; i < 14; i++)
        for(j = 0; j < 14; j++)
            m[i][j].visited = 0;
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            if(m[i][j].c == color && m[i][j].visited == 0) {
                /* Largest conta a maior corrente que tem
                 * da cor dentro do tabuleiro
                 */
                fprintf(stderr, "\tfound pos %d %d\n", i, j);
                x.i = i;
                x.j = j;
                chain = partialDfs(m, x, color, count);
                largest = (chain > largest ? chain : largest);
                count++;
            }
        }
    }
    fprintf(stderr, "\tlargest: %d\n", largest);
    /* Importancia de uma cadeia longa cresce exponencialmente */
    result = fastpow(ChainBase, largest) * largest;
    return (result - 1) * ChainMult;
}

float analizeVantagePos(matrix m, char color) {
    unsigned char i, j;
    float res = 0;
    if(color == 'b') {
        for(i = 0; i < 14; i++) {
            for(j = 0; j < 14; j++) {
                if(m[i][j].c == 'b')
                    res += WhiteStrategy[i][j];
                else if(m[i][j].c == 'p')
                    res -= BlackStrategy[i][j];
            }
        }
    }
    else {
        for(i = 0; i < 14; i++) {
            for(j = 0; j < 14; j++) {
                if(m[i][j].c == 'p')
                    res += BlackStrategy[i][j];
                else if(m[i][j].c == 'b')
                    res -= WhiteStrategy[i][j];
            }
        }
    }
    return correctBounds(res * StratMult);
}

float winningSequence(matrix m, char color, posList* ref) {
    /* devolver 0 ou posInf
     * NULL em ref se não há caminho
     * ou o caminho se há um.
     */
}

float judgeBoard(matrix m, char color) {
    float value = 0;
    matrix_print(m);
    value += analizeVantagePos(m, color);
    fprintf(stderr, "analizeVantagePos: %f\n", value);
    value = correctBounds(value);
    value += dfsbridge(m, color);
    fprintf(stderr, "dfsbridge: %f\n", value);
    value = correctBounds(value);
    value += bridgeFunction(m, color);
    fprintf(stderr, "bridgeFunction: %f\n", value);
    value = correctBounds(value);
    return value;
}
