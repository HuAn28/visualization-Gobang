#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QList>
#include <QPainter>
#include "chessnode.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>

class CheckerBoard
{
public:
    CheckerBoard();
    void RepentStep();
    void AddStep(ChessNode c);
    void NewGame();
    int GetRouteLen();
    ChessNode ShowNode(int x, int y);
    ChessNode ShowRecentStep();
    Lineup GetNodeId(int x, int y);
    bool PlaceNode(int x, int y, Lineup id);
    bool SaveGame(QString path);
    bool ReadGame(QString path);
    bool JudgmentVOD();

public:
    QList<ChessNode> route;
    QPixmap white_piece_img;
    QPixmap black_piece_img;

private:
    int size;
    int len;
    ChessNode **board;
};

#endif // CHECKERBOARD_H
