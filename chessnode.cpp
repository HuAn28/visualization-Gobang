#include "chessnode.h"

ChessNode::ChessNode()
{
    location_x = 0;
    location_y = 0;
    player_id = None;
}

void ChessNode::SetLocation(int x, int y)
{
    location_x = x;
    location_y = y;
}

void ChessNode::SetPlayerId(Lineup id)
{
    player_id = id;
}

void ChessNode::SetChessNode(int x, int y, Lineup id)
{
    location_x = x;
    location_y = y;
    player_id = id;
}

int ChessNode::GetLocationX()
{
    return location_x;
}

int ChessNode::GetLocationY()
{
    return location_y;
}

Lineup ChessNode::GetPlayerId()
{
    return player_id;
}

