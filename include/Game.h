#ifndef GAME_H
#define GAME_H
#include <Block.h>
#include <BlockBoard.h>
#include <vector>

/** @brief Direction
 */
enum DIR {
    UP, DOWN, LEFT, RIGHT
};
class BlockBoard;
class Game
{
    public:
        Game();
        virtual ~Game();
        void init(int size);
        std::vector< std::vector<Block *> > blankGrid();
        void addRandomBlock();
        void render();
        BlockBoard* getBlockBoard() { return mBlockBoard; }
        void move(DIR dir);
        void update(int delta_ms);

    protected:

    private:
        int mSize;
        std::vector< std::vector<Block *> > mBlock;
        friend class BlockBoard;
        BlockBoard *mBlockBoard;

};

#endif // GAME_H
