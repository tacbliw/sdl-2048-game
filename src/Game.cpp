#include "Game.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <stdio.h>
#include <time.h>
#include "SDLUtils.h"

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
    int middle = 100 * mSize + 15 * (mSize + 1);
    mBlockBoard = new BlockBoard(this, (SCREEN_WIDTH - middle)/2, (SCREEN_HEIGHT - middle)/2);

    mBlock = blankGrid();

    addRandomBlock();
    addRandomBlock();

}

/** \brief Create an empty 4x4 grid filled with zeros
 *
 * \return std::vector< std::vector<Block>>
 *
 */
std::vector< std::vector<Block *> > Game::blankGrid()
{
    std::vector< std::vector<Block *> > grid(4, std::vector<Block *>(4, nullptr));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            grid[i][j] = nullptr;
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
            if (mBlock[i][j] == nullptr)
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

        mBlock[blanks[randomPosition].row][blanks[randomPosition].col] = new Block(blanks[randomPosition].row, blanks[randomPosition].col, randomNumber % 100 < 90 ? 2 : 4);
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



void Game::moveVer(int x, int y, int d)
{
	if (mBlock[x + d][y] != nullptr && mBlock[x][y] != nullptr && mBlock[x + d][y]->get_value() == mBlock[x][y]->get_value() && mBlock[x][y]->mergeFrom1 == nullptr && mBlock[x + d][y]->mergeFrom1 == nullptr) // merge
	{
	    Block *f = mBlock[x][y];
		Block *l = mBlock[x + d][y];
        mBlock[x][y] = nullptr;

		mBlock[x + d][y] = new Block(x + d, y, mBlock[x + d][y]->get_value() * 2);
		mBlock[x + d][y]->mergeFrom1 = f;
		mBlock[x + d][y]->mergeFrom2 = l;
	}
	else if (mBlock[x + d][y] == nullptr && mBlock[x][y] != nullptr)
	{
        mBlock[x + d][y] = mBlock[x][y];
		mBlock[x][y] = nullptr;
	}

	if (d < 0)
	{
		if (x + d > 0)
		{
			moveVer(x + d, y, -1);
		}
	}
	else
	{
		if (x + d < 3)
		{
			moveVer(x + d, y, 1);
		}
	}
}

void Game::moveHor(int x, int y, int d)
{
	if (mBlock[x][y] != nullptr && mBlock[x][y + d] != nullptr && mBlock[x][y + d]->get_value() == mBlock[x][y]->get_value() && mBlock[x][y]->mergeFrom1 == nullptr && mBlock[x][y + d]->mergeFrom1 == nullptr) // merge
	{
		Block *f = mBlock[x][y];
		Block *l = mBlock[x][y + d];
		mBlock[x][y] = nullptr;

		mBlock[x][y + d] = new Block(x, y + d, mBlock[x][y + d]->get_value() * 2);
		mBlock[x][y + d]->mergeFrom1 = f;
		mBlock[x][y + d]->mergeFrom2 = l;
	}
	else if (mBlock[x][y + d] == nullptr && mBlock[x][y] != nullptr)
	{
		mBlock[x][y + d] = mBlock[x][y];
		mBlock[x][y] = nullptr;
	}

	if (d < 0)
	{
		if (y + d > 0)
		{
			moveHor(x, y + d, -1);
		}
	}
	else
	{
		if (y + d < 3)
		{
			moveHor(x, y + d, 1);
		}
	}
}

void Game::up()
{
    for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 4; ++j)
		{
			if (mBlock[j][i] != nullptr)
			{
				moveVer(j, i, -1);
			}
		}
	}
}

void Game::down()
{
    for (int i = 0; i < 4; ++i)
	{
		for (int j = 2; j >= 0; --j)
		{
			if (mBlock[j][i] != nullptr)
			{
				moveVer(j, i, 1);
			}
		}
	}
}

void Game::left()
{
    for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 4; ++j)
		{
			if (mBlock[i][j] != nullptr)
			{
				moveHor(i, j, -1);
			}
		}
	}
}

void Game::right()
{
    for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (mBlock[i][2 - j] != nullptr)
			{
				moveHor(i, 2 - j, 1);
			}
		}
	}
}

void Game::move(DIR dir)
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            if (mBlock[i][j] != nullptr && mBlock[i][j]->mergeFrom1 != nullptr)
            {
                delete mBlock[i][j]->mergeFrom1;
                mBlock[i][j]->mergeFrom1 = nullptr;
                delete mBlock[i][j]->mergeFrom2;
                mBlock[i][j]->mergeFrom2 = nullptr;
            }
        }
    }

    switch (dir)
    {
        case UP:
            up();
            break;
        case DOWN:
            down();
            break;
        case LEFT:
            left();
            break;
        case RIGHT:
            right();
            break;
    }

    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            if (mBlock[i][j] != nullptr)
            {
                if (mBlock[i][j]->mergeFrom1 != nullptr)
                {
                    mBlock[i][j]->mergeFrom1->planMove(i, j);
                    mBlock[i][j]->mergeFrom2->planMove(i, j);
                }
                if (!((mBlock[i][j]->get_row() == i) && (mBlock[i][j]->get_col() == j)))
                {
                    mBlock[i][j]->planMove(i, j);
                }
            }
        }
    }

    addRandomBlock();

//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 4; j++)
//        {
//            if (mBlock[i][j] != nullptr)
//                printf("%d ", mBlock[i][j]->get_value());
//            else
//                printf("0 ");
//        }
//        printf("\n");
//    }
//    printf("\n");
}

void Game::update(int delta_ms)
{
    //printf("update every time\n");
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            if (mBlock[i][j] != nullptr)
            {
                if (mBlock[i][j]->mergeFrom1 != nullptr)
                {
                    mBlock[i][j]->mergeFrom1->update(delta_ms);
                    mBlock[i][j]->mergeFrom2->update(delta_ms);
                }
                //printf("update block \n");
                mBlock[i][j]->update(delta_ms);
            }
        }
    }
}
