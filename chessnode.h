#ifndef CHESSNODE_H
#define CHESSNODE_H

#include "config.h"

class ChessNode
{
public:
    ChessNode();
    void SetLocation(int x, int y);
    void SetPlayerId(Lineup id);
    void SetChessNode(int x, int y, Lineup id);
    int GetLocationX();
    int GetLocationY();
    Lineup GetPlayerId();

private:
    int location_x;
    int location_y;
    Lineup player_id;
};

#endif // CHESSNODE_H
