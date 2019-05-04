#include "ScoreBoard.h"
#include <sstream>
#include "Render.h"

static Font scoreBoardFont;

extern void loadScoreBoardMetadata()
{
    const char *fontFile = "Fonts/OpenSans-Bold.ttf";
    scoreBoardFont.init(fontFile, 14);
}

ScoreBoard::ScoreBoard(const char *_title, int _x, int _y, int _w, int _h)
{
    mPoint = 0;
    mPosition.x = _x;
    mPosition.y = _y;

    mTitle = _title;
    mPosition.x = _x;
    mPosition.y = _y;
    mWidth = _w;
    mHeight = _h;

    mTextTexture = new Texture();
    mTexture = new Texture();
    mPointTexture = new Texture();

    mTextTexture->loadTextureFromText(&scoreBoardFont, mTitle, { 0xF9, 0xF6, 0xF2, 0xFF });
    std::stringstream ss;
    ss << mPoint;
    mPointTexture->loadTextureFromText(&scoreBoardFont, ss.str().c_str(), { 0xF9, 0xF6, 0xF2, 0xFF });


    mTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
    mTexture->setAsRenderTarget();
    gRender.setDrawColor({ 0x8F, 0x7A, 0x66, 0xFF });
    gRender.clear();


    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2,
                         (mTexture->getHeight() - mTextTexture->getHeight())/3,
                         NULL);

    mPointTexture->render((mTexture->getWidth() - mPointTexture->getWidth())/2 + mPointTexture->getWidth()/2,
                          (mTexture->getHeight() - mPointTexture->getHeight())*2/3,
                          NULL);

    gRender.setRenderTarget(NULL);
}

void ScoreBoard::addPoint(int point)
{
    mPoint += point;
}

void ScoreBoard::resetPoint()
{
    mPoint = 0;
}

int ScoreBoard::getPoint()
{
    return mPoint;
}

//mTextTexture->loadTextureFromText(&scoreBoardFont, mTitle, { 0xEE, 0xE4, 0xDA, 0xFF });
//mTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);


void ScoreBoard::render()
{
    std::stringstream ss;
    ss << mPoint;
    mPointTexture->loadTextureFromText(&scoreBoardFont, ss.str().c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });

    mTexture->setAsRenderTarget();
    gRender.setDrawColor({ 0xBB, 0xAD, 0xA0 });
    gRender.clear();

    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2,
                         (mTexture->getHeight() - mTextTexture->getHeight())/4,
                         NULL);

    mPointTexture->render((mTexture->getWidth() - mPointTexture->getWidth())/2,
                          (mTexture->getHeight() - mPointTexture->getHeight())*3/4,
                          NULL);

    gRender.setRenderTarget(NULL);
    mTexture->render(mPosition.x, mPosition.y);
}
