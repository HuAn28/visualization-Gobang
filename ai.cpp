#include "ai.h"

AI::AI()
{

}

void AI::InitScore(CheckerBoard checkerboard)
{
    // 清空存储数组和评分数组
    for(int i = 0; i < 17; i++)
    {
        for(int j = 0; j < 17; j++) {
            gameMapVec[i][j] = 0;
            scoreMapVec[i][j] = 0;
        }
    }
    // 重写存储数组
    for(int i = 0; i < 17; i++)
    {
        for(int j = 0; j < 17; j++) {
            gameMapVec[i][j] = 0;
        }
    }
    for(int i = 0; i < checkerboard.GetRouteLen(); i++) {
        int x = checkerboard.route[i].GetLocationX() - 1;
        int y = checkerboard.route[i].GetLocationY() - 1;
        Lineup id = checkerboard.route[i].GetPlayerId();

        // 假设ai下棋永远是白色
        if(id == checkerboard.route[checkerboard.GetRouteLen() - 1].GetPlayerId()) {
            gameMapVec[x][y] = 1;
        }
        else {
            gameMapVec[x][y] = -1;
        }
    }
    // 进行评分
    CalculateScore();
}

void AI::CalculateScore()
{
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0;    // AI连成子的个数
    int emptyNum = 0;  // 各方向空白位的个数

    for(int row = 0; row < 17; row++)
    {
        for(int col = 0; col < 17; col++)
        {
            // 空白点才算
            if(gameMapVec[row][col] == 0)
            {
                // 遍历8个方向
                for(int y = -1; y <= 1; y++)
                {
                    for(int x = -1; x<= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
                        // x=0，y=0 不是一个方向
                        if(!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4個子

                            // 对玩家黑子评分(正反两个方向)
                            for(int i = 1; i <= 4; i++) {
                                if(row + i * y > 0 && row + i * y < 17 &&
                                   col + i * x > 0 && col + i * x < 17 &&
                                   gameMapVec[row + i * y][col + i * x] == 1) {  // 真人玩家的子
                                    personNum++;
                                }
                                else if(row + i * y > 0 && row + i * y < 17 &&
                                        col + i * x > 0 && col + i * x < 17 &&
                                        gameMapVec[row + i * y][col + i * x] == 0){ //空白位
                                    emptyNum++;
                                    break;
                                }
                                else{ //出边界，或有白子
                                        break;
                                }
                            }
                            for(int i = 1; i <= 4; i++) {
                                if(row - i * y > 0 && row - i * y < 17 &&
                                   col - i * x > 0 && col - i * x < 17 &&
                                   gameMapVec[row - i * y][col - i * x] == 1) { //真人玩家的子
                                    personNum++;
                                }
                                else if(row - i * y > 0 && row - i * y < 17 &&
                                        col - i * x > 0 && col - i * x < 17 &&
                                        gameMapVec[row - i * y][col - i * x] == 0){ //空白位
                                    emptyNum++;
                                    break;
                                }
                                else{ //出边界，或有白子
                                    break;
                                }
                            }

                            if(personNum == 1){                // 杀2
                                scoreMapVec[row][col]+=10;
                            }
                            else if(personNum == 2){           // 杀3
                                if(emptyNum == 1) {
                                    scoreMapVec[row][col] += 30;
                                }
                                else if(emptyNum == 2) {
                                    scoreMapVec[row][col]+=40;
                                }
                            }
                            else if(personNum == 3){           // 杀4
                                //量變空位不一樣，優先級不一樣
                                if(emptyNum == 1) {
                                    scoreMapVec[row][col] += 60;
                                }
                                else if(emptyNum == 2) {
                                    scoreMapVec[row][col] += 110;
                                }
                            }
                            else if(personNum == 4) {           // 杀5
                                scoreMapVec[row][col]+=10100;
                            }

                            // 进行一次清空
                            emptyNum = 0;

                            // 对AI白子评分
                            for(int i = 1; i <= 4; i++) {
                                if(row + i * y > 0 && row + i * y < 17 &&
                                   col + i * x > 0 && col + i * x < 17 &&
                                   gameMapVec[row + i * y][col + i * x] == -1) { // AI的子
                                    botNum++;
                                }
                                else if(row + i * y > 0 && row + i * y < 17 &&
                                        col + i * x > 0 && col + i * x < 17 &&
                                        gameMapVec[row+i*y][col+i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }
                                else{ // 出边界
                                    break;
                                }
                            }
                            for(int i = 1; i <= 4; i++) {
                                if(row - i * y > 0 && row - i * y < 17 &&
                                   col - i * x > 0 && col - i * x < 17 &&
                                   gameMapVec[row - i * y][col - i * x] == -1) { //AI的子
                                        botNum++;
                                }
                                else if(row - i * y > 0 && row - i * y < 17 &&
                                        col - i * x > 0 && col - i * x < 17 &&
                                        gameMapVec[row-i*y][col-i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }
                                else{ // 出边界
                                    break;
                                }
                            }

                            if(botNum == 0){
                                scoreMapVec[row][col] += 5;  // 活1
                            }
                            else if(botNum == 1){
                                scoreMapVec[row][col] += 10; // 活2
                            }
                            else if(botNum == 2){            // 活3
                                if(emptyNum == 1) {
                                    scoreMapVec[row][col] += 25;
                                }
                                else if(emptyNum == 2) {
                                    scoreMapVec[row][col] += 50;
                                }
                            }
                            else if(botNum == 3){            // 活4
                                if(emptyNum == 1) {
                                    scoreMapVec[row][col] += 55;
                                }
                                else if(emptyNum == 2) {
                                    scoreMapVec[row][col] += 100;
                                }
                            }
                            else if(botNum >= 4){            // 活5
                                scoreMapVec[row][col] += 20000;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool AI::ActionByAI(int *posx, int *posy)
{
    // 计算评分
    CalculateScore();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    std::vector<std::pair<int,int>> maxPoints;

    for(int row = 1; row < 17; row++) {
        for(int col = 1; col < 17; col++) {
            // 前提是这个坐标是空的
            if(gameMapVec[row][col] == 0) {
                if(scoreMapVec[row][col] > maxScore) {     // 找最大数和坐标
                    maxPoints.clear();
                    maxScore = scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row,col));
                }
                else if(scoreMapVec[row][col] == maxScore){   // 如果有多个最大值就将他们存储起來，在后面的代码随机抽1个
                    maxPoints.push_back(std::make_pair(row,col));
                }
            }
        }
    }

    // 随机选择一个点，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % maxPoints.size();
    std::pair<int,int> pointPair = maxPoints.at(index);
    *posx = pointPair.first + 1;
    *posy = pointPair.second + 1;
}



