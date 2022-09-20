#ifndef AI_H
#define AI_H

#include "checkerboard.h"
#include "config.h"
#include <QDebug>

class AI
{
public:
    AI();
    void InitScore(CheckerBoard checkerboard);
    void CalculateScore();
    bool ActionByAI(int *posx, int *posy);

public:
    // 存储当前游戏棋盘和棋子的情况，空白为0，黑子1，白子-1
    int gameMapVec[17][17];
    // 存储各个点位的评分情况，作为AI下棋依据
    int scoreMapVec[17][17];
};

#endif // AI_H
