#include "BlockBoard.h"
#include "Render.h"
#include "Texture.h"
#include "Game.h"
#include <stdio.h>

static Font gameOverFont;

const SDL_Color BLOCKBOARD_BACKGROUND_COLOR = {0xBB, 0xAD, 0xA0};
const SDL_Color BLOCKBOARD_HOLDER_COLOR = {238, 228, 218, 125};
const SDL_Color BLOCKBOARD_GAMEOVER_MASK_COLOR = {238, 228, 218, static_cast<int>(0.5 * 255)};
const SDL_Color BLOCKBOARD_GAMEOVER_TEXT_COLOR = { 0x77, 0x6E, 0x65, 0xFF };


extern void loadBlockBoardMetadata()
{
    const char *fontFile = "Fonts/OpenSans-Bold.ttf";
    gameOverFont.init(fontFile, 60);
}

const int BLOCK_SIZE = 100;
const int GRID_SPACING = 15;

/** @brief Set Game pointer
 *
 * @param pGame Game*
 * Game pointer is set to get size of board.
 */
BlockBoard::BlockBoard(Game *pGame, int _mX, int _mY) : mX(_mX), mY(_mY), m_pGame(pGame) {}

/** @brief Render a board and holder to screen
 *
 * @return void
 * First calculate the grid size, then draw a gridSize x gridSize rectangle, then draw holder for block.
 *
 */
void BlockBoard::render()
{
    const int gridSize = getWidth();

    gRender.setDrawColor(BLOCKBOARD_BACKGROUND_COLOR);
    gRender.fillRect(mX, mY, gridSize, gridSize);

    Texture *holder = new Texture();
    holder->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BLOCK_SIZE, BLOCK_SIZE);
    holder->setAsRenderTarget();
    holder->setBlendMode();
    gRender.setDrawColor(BLOCKBOARD_HOLDER_COLOR);
    gRender.clear();
    gRender.setRenderTarget(nullptr);

    for (int i = 0; i < m_pGame->mSize; i++)
    {
        for (int j = 0; j < m_pGame->mSize; j++)
        {
            holder->render(mX + GRID_SPACING + i * (BLOCK_SIZE + GRID_SPACING), mY + GRID_SPACING + j * (BLOCK_SIZE + GRID_SPACING));
        }
    }

    delete holder;

    for (int i = 0; i < m_pGame->mSize; i++)
    {
        for (int j = 0; j < m_pGame->mSize; j++)
        {
            if (m_pGame->mBlock[i][j] != nullptr)
            {
                if (m_pGame->mBlock[i][j]->mergeFrom1 != nullptr)
                {
                    m_pGame->mBlock[i][j]->mergeFrom1->render(mX + GRID_SPACING, mY + GRID_SPACING);
                    m_pGame->mBlock[i][j]->mergeFrom2->render(mX + GRID_SPACING, mY + GRID_SPACING);
                }
                m_pGame->mBlock[i][j]->render(mX + GRID_SPACING, mY + GRID_SPACING);
            }
        }
    }

    if (m_pGame->mGameOver)
    {
        Texture *gameOverMask = new Texture();
        Texture *gameOverText = new Texture();
        gameOverText->loadTextureFromText(&gameOverFont, "Game Over", BLOCKBOARD_GAMEOVER_TEXT_COLOR);

        gameOverMask->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gridSize, gridSize);
        gameOverMask->setBlendMode();
        gameOverMask->setAsRenderTarget();
        gRender.setDrawColor(BLOCKBOARD_GAMEOVER_MASK_COLOR);
        gRender.clear();
        gameOverText->render((gridSize - gameOverText->getWidth())/2, (gridSize - gameOverText->getHeight())/2);

        gRender.setRenderTarget(NULL);
        gameOverMask->render(mX, mY);
        delete gameOverMask;
        delete gameOverText;
    }

    // test
    //gRender.present();
}

int BlockBoard::getWidth()
{
    return BLOCK_SIZE * m_pGame->mSize + GRID_SPACING * (m_pGame->mSize + 1);
}
