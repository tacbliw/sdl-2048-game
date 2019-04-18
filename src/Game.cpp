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
    std::vector< std::vector<Block> > grid(mSize, std::vector<Block>(mSize, Block(0, 0, 0)));
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
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
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
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

/** \brief left-shift all non zero blocks in one line.
 *
 * \param lineIndex int
 * \return void
 *
 */
void Game::leftShiftLine(int lineIndex)
{
    std::vector<Block> temp(mSize, Block(0, 0, 0));
    int tempIndex = 0;
    for (int i = 0; i < mSize; i++)
    {
        if (mBlock[lineIndex][i].get_value() != 0)
        {
            temp[tempIndex] = mBlock[lineIndex][i];
            tempIndex++;
        }
    }

    for (int i = 0; i < mSize; i++)
    {
        mBlock[lineIndex][i] = temp[i];
        mBlock[lineIndex][i].set_row(lineIndex);
        mBlock[lineIndex][i].set_col(i);
    }
}

/** \brief merge and calculate sum of blocks in one line.
 *
 * \param lineIndex int
 * \return void
 *
 */
void Game::mergeAndSum(int lineIndex)
{
    for (int i = 0; i < mSize - 1; i++)
    {
        if (mBlock[lineIndex][i].get_value() == mBlock[lineIndex][i+1].get_value())
        {
            mBlock[lineIndex][i].set_value(2 * mBlock[lineIndex][i].get_value());
            mBlock[lineIndex][i+1].set_value(0);
        }
    }
}

/** \brief left-shift all blocks in grid.
 *
 * \return void
 *
 */
void Game::leftShiftGrid()
{
    for (int i = 0; i < mSize; i++)
    {
        leftShiftLine(i);
        mergeAndSum(i);
        leftShiftLine(i);
    }
    addRandomBlock();
    printBoard();
    std::cout << "\n";
}

/** \brief rotate the board 90 degrees clockwise.
 *
 * \return void
 *
 */
void Game::rotateClockWise()
{
    std::vector< std::vector<Block> > copyBoard(mSize, std::vector<Block>(mSize, Block(0, 0, 0)));
    int row = 0;
    int col = mSize - 1;

    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            copyBoard[i][j] = mBlock[row++][col];
            copyBoard[i][j].set_row(i);
            copyBoard[i][j].set_col(j);
        }
        col++;
        row = 0;
    }
    mBlock = copyBoard;
}

void Game::printBoard()
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            std::cout << mBlock[i][j].get_value() << " (" << mBlock[i][j].get_row() << ", " << mBlock[i][j].get_col() << ") ";
        }
        std::cout << "\n";
    }
}

/** @brief Render board game.
 *
 * @return void
 * Render block board by passing 2D blocks array.
 */
void Game::render()
{
    mBlockBoard->render(mBlock);
}
