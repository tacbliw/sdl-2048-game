#include "BlockBoard.h"
#include "Render.h"
#include "Texture.h"
#include "Game.h"
#include <stdio.h>

const int blockSize = 100;
const int gridSpacing = 15;

/** @brief Set Game pointer
 *
 * @param pGame Game*
 * Game pointer is set to get size of board.
 */
BlockBoard::BlockBoard(Game *pGame, int _mX, int _mY) : mX(_mX), mY(_mY)
{
    m_pGame = pGame;


}

/** @brief Render a board and holder to screen
 *
 * @return void
 * First calculate the grid size, then draw a gridSize x gridSize rectangle, then draw holder for block.
 *
 */
void BlockBoard::render(std::vector< std::vector<Block*> > block)
{
    const int gridSize = this->getWidth();

    gRender.setDrawColor({0xBB, 0xAD, 0xA0});
    gRender.fillRect(mX, mY, gridSize, gridSize);

    Texture *holder = new Texture();
    holder->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, blockSize, blockSize);
    holder->setAsRenderTarget();
    holder->setBlendMode();
    gRender.setDrawColor({238, 228, 218, 125});
    gRender.clear();
    gRender.setRenderTarget(NULL);

    for (int i = 0; i < m_pGame->mSize; i++)
    {
        for (int j = 0; j < m_pGame->mSize; j++)
        {
            holder->render(mX + gridSpacing + i * (blockSize + gridSpacing), mY + gridSpacing + j * (blockSize + gridSpacing));
        }
    }



    for (int i = 0; i < m_pGame->mSize; i++)
    {
        for (int j = 0; j < m_pGame->mSize; j++)
        {
            if (block[i][j] != nullptr)
            {
                block[i][j]->render(mX + gridSpacing, mY + gridSpacing);
            }
        }
    }


    // test
    //gRender.present();
}

int BlockBoard::getWidth()
{
    return blockSize * m_pGame->mSize + gridSpacing * (m_pGame->mSize + 1);
}
