#include "Game.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <stdio.h>
#include <time.h>

struct Position {int row; int col;};

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

/** @brief Initialize game
 *
 * @param size int
 * @return void
 *  Calculate area of board game, create 2D blocks array, each fill with nullptr, add 2 random block.
 */
void Game::init(int size)
{
    mSize = size;

    int len = size * size;
    mBlockBoard = new BlockBoard(this);

    mBlock = blankGrid();

    addRandomBlock();
    addRandomBlock();
    addRandomBlock();


    /*for (int i = 0; i < mSize * mSize; i++)
    {
        if (mBlock[i] != nullptr)
            printf("%d ", mBlock[i]->get_value());
    }*/

}

/** \brief Create an empty 4x4 grid filled with zeros
 *
 * \return std::vector< std::vector<Block>>
 *
 */
std::vector< std::vector<Block> > Game::blankGrid()
{
    std::vector< std::vector<Block> > grid(4, std::vector<Block>(4, Block(0, 0, 0)));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Block newBlock(i, j, 0);
            grid[i][j] = newBlock;
        }
    }

    return grid;
}

/** @brief Add random block
 *
 * @return void
 * Get empty blocks, then get a block in these blocks randomly, then set 2 or 4 to block's value randomly too.
 */
void Game::addRandomBlock()
{
    srand(time(NULL));
    std::vector <Position> blanks;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mBlock[i][j].get_value() == 0)
            {
                Position p = {i, j};
                blanks.push_back(p);
            }
        }
    }

    if (!blanks.empty())
    {
        int randomNumber = rand();
        int randomPosition = randomNumber % blanks.size();
        randomNumber = rand();

        mBlock[blanks[randomPosition].row][blanks[randomPosition].col].set_value(randomNumber % 2 ? 2 : 4);
    }
}


/** @brief Render board game
 *
 * @return void
 * Render block board by passing 2D blocks array.
 */
void Game::render()
{
    mBlockBoard->render(mBlock);
}
