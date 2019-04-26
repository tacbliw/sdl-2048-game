#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    this->mPoint = 0;
    this->mX = 0;
    this->mY = 0;
}

void ScoreBoard::addPoint(int point)
{
    this->mPoint += point;
}

void ScoreBoard::resetPoint()
{
    this->mPoint = 0;
}

int ScoreBoard::getPoint()
{
    return mPoint;
}


void ScoreBoard::render()
{
    /**< Add score board render here */

}
