#ifndef GAME_H
#define GAME_H
#include <Block.h>
#include <BlockBoard.h>
#include <ScoreBoard.h>
#include <vector>
#include <HighScoreBoard.h>

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

        // support functions
        std::vector< std::vector<Block *> > blankGrid();
        void storeBoard();
        bool gridChanged();
        bool noMove();

        // game behavior
        void addRandomBlock();
        void gameOver();
        void newGame();
        void win();

        //
        BlockBoard* getBlockBoard() { return mBlockBoard; }

        // game controler
        void move(DIR dir);

        // render and animation
        void render();
        void update(int delta_ms);

    private:
        // local variables
        int mSize;
        std::vector< std::vector<Block *> > mBlock;
        std::vector< std::vector<int> > previousMBlock;
        friend class BlockBoard;
        BlockBoard *mBlockBoard;
        ScoreBoard *mScoreBoard;
        HighScoreBoard *mHighScoreBoard;
        bool mGameOver;
        bool mWin, mWon;

        // gameplay functions
        void up();
        void down();
        void left();
        void right();
        void moveVer(int x, int y, int d);
        void moveHor(int x, int y, int d);
};

#endif // GAME_H
