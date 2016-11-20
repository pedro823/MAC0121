#include "positionHandler.h"
#include "strategy.h"
#include <limits.h>

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

/* Tunado à mão depois de vários jogos. */
static const float BridgeMult = 1;
static const float LadderMult = 1;
static const float StratMult = 1;
static const float BlockMult = 1;
static const float CompleteMult = 1;
static const float OpenSpaceMult = 1;

float correctBounds(float n) {
    if(n > posInf)
    n = posInf;
    if(n < negInf)
    n = negInf;
    return n;
}

float analizeVantagePos(matrix m) {
    unsigned char i, j;
    float res = 0;
    for(i = 0; i < 14; i++) {
        for(j = 0; j < 14; j++) {
            if(m[i][j].c == 'b')
                res += WhiteStrategy[i][j];
            else if(m[i][j].c == 'p')
                res -= BlackStrategy[i][j];
        }
    }
    return correctBounds(res * StratMult);
}

float winningSequence(matrix m) {

}

float judgeBoard(matrix m, char color) {

}
