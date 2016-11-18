#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "positionHandler.h"

double isBridge(matrix m, pos x, char color);

double isLadder(matrix m, pos x, char color);

double stratPlace(matrix m, pos x, char color);

double blockPath(matrix m, pos x, char color);

double completeBridge(matrix m, pos x, char color);

double openSpace(matrix m, pos x, char color);


#endif
