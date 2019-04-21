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
    previousMBlock = std::vector< std::vector<int> >(mSize, std::vector<int>(mSize, 0));

    addRandomBlock();

    //mBlock[1][1]->set_value(2);
    //addRandomBlock();
    //addRandomBlock();



    /*for (int i = 0; i < mSize * mSize; i++)
    {
        if (mBlock[i] != nullptr)
            printf("%d ", mBlock[i]->get_value());
    }*/

}

//=================== SUPPORT FUNCTIONS ================
/** \brief Create an empty 4x4 grid filled with zeros
 *
 * \return std::vector< std::vector<Block>>
 *
 */
std::vector< std::vector<Block*> > Game::blankGrid()
{
    std::vector< std::vector<Block*> > grid(mSize, std::vector<Block*>(mSize, nullptr));
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            grid[i][j] = new Block(i, j, 0);
        }
    }

    return grid;
}

/** \brief store a copy of values in current mBlock.
 *
 * \return void
 *
 */
void Game::storeGrid()
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            previousMBlock[i][j] = mBlock[i][j]->get_value();
        }
    }
}

/** \brief Compare mBlock with previousMBlock, return true if different.
 *
 * \return bool
 *
 */
bool Game::gridChanged()
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            if (mBlock[i][j]->get_value() != previousMBlock[i][j])
            {
                return true;
            }
        }
    }
    return false;
}
//=============== GAME BEHAVIOURS ==================
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
            if (mBlock[i][j]->get_value() == 0)
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

        mBlock[blanks[randomPosition].row][blanks[randomPosition].col]->set_value(randomNumber % 2 ? 2 : 4);
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
    std::vector<Block *> temp(mSize, nullptr);
    int tempIndex = 0;
    for (int i = 0; i < mSize; i++)
    {
        if (mBlock[lineIndex][i]->get_value() != 0)
        {
            temp[tempIndex] = mBlock[lineIndex][i];
            tempIndex++;
        }
        else
        {
            delete mBlock[lineIndex][i];
            mBlock[lineIndex][i] = nullptr;
        }
    }

    for (int i = 0; i < mSize; i++)
    {
        if (temp[i] != nullptr) mBlock[lineIndex][i] = temp[i];
        else mBlock[lineIndex][i] = new Block(lineIndex, i, 0);
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
        if (mBlock[lineIndex][i]->get_value() == mBlock[lineIndex][i+1]->get_value())
        {
            mBlock[lineIndex][i]->set_value(2 * mBlock[lineIndex][i]->get_value());
            mBlock[lineIndex][i+1]->set_value(0);
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
}

/** \brief rotate the board 90 degrees counter clockwise.
 *
 * \return void
 *
 */
void Game::rotateLeft()
{
    std::vector< std::vector<Block*> > copyBoard(mSize, std::vector<Block*>(mSize, nullptr));
    int row = 0;
    int col = mSize - 1;

    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            copyBoard[i][j] = mBlock[row++][col];
        }
        col--;
        row = 0;
    }
    mBlock = copyBoard;
}

void Game::rotateRight()
{
    std::vector< std::vector<Block*> > copyBoard(mSize, std::vector<Block*>(mSize, nullptr));
    int row = mSize - 1;
    int col = 0;

    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            copyBoard[i][j] = mBlock[row--][col];
        }
        row = mSize - 1;
        col++;
    }
    mBlock = copyBoard;
}

//================= DEBUG =========================
void Game::printBoard()
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            std::cout << mBlock[i][j]->get_value() << " ";
//                      << " (" << mBlock[i][j]->get_row()
//                      << ", " << mBlock[i][j]->get_col()
//                      << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//=================== GAME ===================

/** \brief Execute movement commands from user input.
 *   Including check grid's changes, adding random blocks.
 *
 * \param sdlKeyScancode SDL_Scancode
 * \return void
 *
 */
void Game::movementExecute(SDL_Scancode sdlKeyScancode)
{
    storeGrid();

    switch (sdlKeyScancode)
    {
    case SDL_SCANCODE_UP:
        up();
        break;
    case SDL_SCANCODE_DOWN:
        down();
        break;
    case SDL_SCANCODE_LEFT:
        left();
        break;
    case SDL_SCANCODE_RIGHT:
        right();
        break;
    default:
        printf("Unhandled movement key.\n");
    }

    if (gridChanged())
    {
        addRandomBlock();
        for (int i = 0; i < mSize; i++)
        {
            for (int j = 0; j < mSize; j++)
            {
                mBlock[i][j]->set_row(i);
                mBlock[i][j]->set_col(j);
                mBlock[i][j]->updateMPosition();
            }
        }
    }
    printBoard();
}

void Game::up()
{
    rotateLeft();
    leftShiftGrid();
    rotateRight();
}

void Game::down()
{
    rotateRight();
    leftShiftGrid();
    rotateLeft();
}

void Game::left()
{
    leftShiftGrid();
}

void Game::right()
{
    rotateLeft();
    rotateLeft();
    leftShiftGrid();
    rotateLeft();
    rotateLeft();
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

void Game::update(int delta_ms)
{
    //printf("update every time\n");
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            if (mBlock[i][j]->get_value() != 0)
                mBlock[i][j]->update(delta_ms);
        }
    }
}
