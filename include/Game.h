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

        std::vector< std::vector<Block*> > blankGrid();
        void storeGrid();
        bool gridChanged();

        void addRandomBlock();
        void leftShiftLine(int lineIndex);
        void mergeAndSum(int lineIndex);
        void leftShiftGrid();
        void rotateLeft();
        void rotateRight();

        //debug
        void printBoard();

        // Playing
        void up();
        void down();
        void left();
        void right();
        void movementExecute(SDL_Scancode sdlKeyScancode);

        BlockBoard* getBlockBoard() { return mBlockBoard; }
        void render();

    protected:

    private:
        int mSize;
        std::vector< std::vector<Block*> > mBlock;
        friend class BlockBoard;
        BlockBoard *mBlockBoard;

        std::vector< std::vector<int> > previousMBlock;

};

#endif // GAME_H
