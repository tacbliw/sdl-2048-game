#include "Game.h"
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <stdio.h>
#include <time.h>

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
    mBlock = new Block*[len];
    mBlockBoard = new BlockBoard(this);
    std::fill(mBlock, mBlock + len, nullptr);

    addRandomBlock();
    addRandomBlock();

    /*for (int i = 0; i < mSize * mSize; i++)
    {
        if (mBlock[i] != nullptr)
            printf("%d ", mBlock[i]->get_value());
    }*/

}

/** @brief Get empty block
 *
 * @return std::vector <int>
 *  Iterate through all block, if one is nullptr then push back to result array.
 */
std::vector<int> Game::getEmptyBlocks()
{
    std::vector<int> emptyBlocks;
    for (int i = 0; i < mSize * mSize; i++)
    {
        if (mBlock[i] == nullptr)
        {
            printf("block %d is empty\n", i);
            emptyBlocks.push_back(i);
        }
    }
    return std::move(emptyBlocks);
}

/** @brief Add random block
 *
 * @return void
 * Get empty blocks, then get a block in these blocks randomly, then set 2 or 4 to block's value randomly too.
 */
void Game::addRandomBlock()
{
    std::vector<int> emptyBlocks = getEmptyBlocks();
    if (emptyBlocks.empty())
    {
        return;
    }

    //std::random_device rd;
    //std::mt19937 mt(rd());
    //std::uniform_int_distribution<int> dist(0, emptyBlocks.size() - 1);
    srand(time(NULL));
    auto cell = emptyBlocks[rand() % (emptyBlocks.size() - 1)];

    int value = (rand() % (emptyBlocks.size() - 1)) % 2 ? 2 : 4;
    Block *block = new Block(cell / mSize, cell % mSize, value);
    mBlock[cell] = block;
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
