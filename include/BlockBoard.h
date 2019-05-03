#ifndef BLOCKBOARD_H
#define BLOCKBOARD_H
#include <vector>
#include "Game.h"

class Game;
class BlockBoard
{
    public:
        BlockBoard(Game* pGame, int _mX, int _mY);
        void render();
        void setPosition(int x, int y) {mX = x; mY = y;}
        int getWidth();
    private:
        int mX;
        int mY;
        Game *m_pGame;
};

extern void loadBlockBoardMetadata();

#endif // BLOCKBOARD_H
