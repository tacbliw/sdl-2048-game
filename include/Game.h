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
        std::vector<int> getEmptyBlocks();
        void addRandomBlock();
        void render();
        BlockBoard* getBlockBoard() { return mBlockBoard; }
    protected:

    private:
        int mSize;
        Block **mBlock;
        friend class BlockBoard;
        BlockBoard *mBlockBoard;

};

#endif // GAME_H
