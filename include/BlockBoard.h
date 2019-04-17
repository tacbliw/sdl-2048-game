#ifndef BLOCKBOARD_H
#define BLOCKBOARD_H
#include <vector>
#include "Game.h"

class Game;
class BlockBoard
{
    public:
        BlockBoard(Game* pGame);
        void render(std::vector< std::vector<Block> > block);
        void setPosition(int x, int y) {mX = x; mY = y;}
        int getWidth();
    private:
        int mX;
        int mY;
        Game *m_pGame;
};

#endif // BLOCKBOARD_H
