#include "HighScoreBoard.h"
#include <sstream>
#include "Render.h"
#include <fstream>

static Font highScoreFont;

extern void loadHighScoreBoardMetadata()
{
    const char *fontFile = "Fonts/OpenSans-Bold.ttf";
    highScoreFont.init(fontFile, 14);
}

HighScoreBoard::HighScoreBoard(const char *_title, int _x, int _y, int _w, int _h)
{
    mHighScore = 0;
    mPosition.x = _x;
    mPosition.y = _y;

    mTitle = _title;
    mPosition.x = _x;
    mPosition.y = _y;
    mWidth = _w;
    mHeight = _h;

    mTextTexture = new Texture();
    mTexture = new Texture();
    mHighScoreTexture = new Texture();

    loadHighScore();

    mTextTexture->loadTextureFromText(&highScoreFont, mTitle, { 0xF9, 0xF6, 0xF2, 0xFF });
    std::stringstream ss;
    ss << mHighScore;
    mHighScoreTexture->loadTextureFromText(&highScoreFont, ss.str().c_str(), { 0xF9, 0xF6, 0xF2, 0xFF });


    mTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
    mTexture->setAsRenderTarget();
    gRender.setDrawColor({ 0x8F, 0x7A, 0x66, 0xFF });
    gRender.clear();


    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2,
                         (mTexture->getHeight() - mTextTexture->getHeight())/3,
                         NULL);

    mHighScoreTexture->render((mTexture->getWidth() - mHighScoreTexture->getWidth())/2 + mHighScoreTexture->getWidth()/2,
                          (mTexture->getHeight() - mHighScoreTexture->getHeight())*2/3,
                          NULL);

    gRender.setRenderTarget(NULL);
}



void HighScoreBoard::render()
{
    std::stringstream ss;
    ss << mHighScore;
    mHighScoreTexture->loadTextureFromText(&highScoreFont, ss.str().c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });

    mTexture->setAsRenderTarget();
    gRender.setDrawColor({ 0xBB, 0xAD, 0xA0 });
    gRender.clear();

    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2,
                         (mTexture->getHeight() - mTextTexture->getHeight())/4,
                         NULL);

    mHighScoreTexture->render((mTexture->getWidth() - mHighScoreTexture->getWidth())/2,
                          (mTexture->getHeight() - mHighScoreTexture->getHeight())*3/4,
                          NULL);

    gRender.setRenderTarget(NULL);
    mTexture->render(mPosition.x, mPosition.y);

    delete mHighScoreTexture;
}

int HighScoreBoard::getHighScore()
{
    return mHighScore;
}

void HighScoreBoard::loadHighScore()
{
        std::fstream f;
        f.open("data/highscore.txt");
        if (f.is_open())
        {
            f >> mHighScore;
        }
        else
        {
            printf("daed game\n");
        }
}

void HighScoreBoard::setHighScore(int score)
{
    mHighScore = score;
}
