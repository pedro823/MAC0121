#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "positionHandler.h"

float judgeBoard(matrix m, char color);

char opsColor(char color);

pos completeWinningsequence(matrix m, posList x, char color);

#endif
