#include "checkerboard.h"

CheckerBoard::CheckerBoard()
{
    size = 19;
    len = 0;
    white_piece_img.load(":/img/White.png");
    black_piece_img.load(":/img/Black.png");
    board = new ChessNode*[size+2];
    for(int i = 0; i < size + 2; i++) {
        board[i] = new ChessNode[size+2];
        for(int j = 0; j < size + 2; j++) {
            board[i][j].SetChessNode(i, j, None);
        }
    }
}

void CheckerBoard::RepentStep()
{
    if(len > 0) {
        ChessNode tmp = route.takeAt(len-1);
        board[tmp.GetLocationX()][tmp.GetLocationY()].SetChessNode(tmp.GetLocationX(), tmp.GetLocationY(), None);
        len--;
    }
    return;
}

void CheckerBoard::AddStep(ChessNode c)
{
    route.append(c);
    this->len++;
}

void CheckerBoard::NewGame()
{
    for(int i = 0; i < size + 2; i++) {
        for(int j = 0; j < size + 2; j++) {
            board[i][j].SetChessNode(i, j, None);
        }
    }
    qDebug() << "成功移除:" << route.size() << "步";
    for(int i = route.size(); i >= 0; i--)
    {
        route.removeAt(i);
    }
    this->len = 0;
}

int CheckerBoard::GetRouteLen()
{
    return len;
}

ChessNode CheckerBoard::ShowNode(int x, int y)
{
    if (x >= 1 && y >= 1 && x <= size && y <= size) {
        return board[x][y];
    }
    return board[0][0];
}

ChessNode CheckerBoard::ShowRecentStep()
{
    if(len > 0) {
        return route[len-1];
    }
    return board[0][0];
}

Lineup CheckerBoard::GetNodeId(int x, int y)
{
    if (x < 1 && y < 1 && x > size && y > size) {
        return Other;
    }
    if (board[x][y].GetPlayerId() != None) {
        return board[x][y].GetPlayerId();
    }
    else {
        return None;
    }
    return Other;
}

bool CheckerBoard::PlaceNode(int x, int y, Lineup id)
{
    if (x < 1 && y < 1 && x > size && y > size) {
        return false;
    }
    if (board[x][y].GetPlayerId() != None) {
        return false;
    }
    if (x >= 1 && y >= 1 && x <= size && y <= size) {
        board[x][y].SetChessNode(x, y, id);
        AddStep(board[x][y]);
        return true;
    }
    return false;
}

bool CheckerBoard::SaveGame(QString path)
{
    QFile file(path);
    // 设置打开方式
    file.open(QIODevice::Append);
    char text[7];
    text[2] = ',';
    text[5] = '\n';
    text[6] = '\0';
    for(int i = 0; i < len; i++) {
        text[0] = char(route[i].GetLocationX() / 10 + 48);
        text[1] = char(route[i].GetLocationX() % 10 + 48);
        text[3] = char(route[i].GetLocationY() / 10 + 48);
        text[4] = char(route[i].GetLocationY() % 10 + 48);
        file.write(text);
    }
    file.close();
    return true;
}

bool CheckerBoard::ReadGame(QString path)
{
    qDebug() << path;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array;
    array = file.readLine();  // 按行读
    if(array == "None\n") {
        qDebug() << array;
    }
    else if(array == "White\n") {
        qDebug() << array;
    }
    else if(array == "Black\n") {
        qDebug() << array;
    }
    else {
        return false;
    }

    while(!file.atEnd())
    {
        Lineup id = None;
        if(GetRouteLen() == 0) {
            id = Black;
        }
        else if (GetRouteLen() > 0)
        {
            if(route[GetRouteLen() -1].GetPlayerId() == White) {
                id = Black;
            }
            else if (route[GetRouteLen() -1].GetPlayerId() == Black) {
                id = White;
            }
            else {
                qDebug() << "代码有错误";
            }
        }
        else {
            qDebug() << "代码有错误";
        }
        array = file.readLine();
        qDebug() << array;
        PlaceNode((int(array[0]) - 48) * 10 + int(array[1]) - 48, (int(array[3]) - 48) * 10 + int(array[4]) - 48, id);
    }

    return true;
}

// 朴素遍历的方法判断胜负
bool CheckerBoard::JudgmentVOD()
{
    for(int i = 5; i <= size; i++) {
        for(int j = 5; j <= size; j++) {
            if(board[i][j].GetPlayerId() != None) {
                int k, num;
                num = 1;
                for(k = 1; k < 5; k++) {
                    if(board[i - k][j].GetPlayerId() == board[i][j].GetPlayerId()) {
                        num++;
                    }
                    else{
                        break;
                    }
                }
                if(num == 5) {
                    return true;
                }

                num = 1;
                for(k = 1; k < 5; k++) {
                    if(board[i][j - k].GetPlayerId() == board[i][j].GetPlayerId()) {
                        num++;
                    }
                    else{
                        break;
                    }
                }
                if(num == 5) {
                    return true;
                }

                num = 1;
                for(k = 1; k < 5; k++) {
                    if(board[i - k][j - k].GetPlayerId() == board[i][j].GetPlayerId()) {
                        num++;
                    }
                    else{
                        break;
                    }
                }
                if(num == 5) {
                    return true;
                }

                num = 1;
                for(k = 1; k < 5; k++) {
                    if(board[i - k][j - k].GetPlayerId() == board[i][j].GetPlayerId()) {
                        num++;
                    }
                    else{
                        break;
                    }
                }
                if(num == 5) {
                    return true;
                }
            }
        }
    }

    for(int i = 5; i <= size; i++) {
        for(int j = 1; j <= size - 4; j++) {
            if(board[i][j].GetPlayerId() != None) {
                int k, num;
                num = 1;
                for(k = 1; k < 5; k++) {
                    if(board[i - k][j + k].GetPlayerId() == board[i][j].GetPlayerId()) {
                        num++;
                    }
                    else{
                        break;
                    }
                }
                if(num == 5) {
                    return true;
                }
            }
        }
    }
    return false;
}
