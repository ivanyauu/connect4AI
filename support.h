#ifndef SUPPORT_H
#define SUPPORT_H

#include "provided.h"
#include <iostream>

int rate(Scaffold scaffold, int prevCol, int nToWin, int checker);
int determineBestMove(Scaffold scaffold, int depth, int color, bool isMax, int nToWin, int prevCol, int alpha, int beta);

#endif // !SUPPORT_H

