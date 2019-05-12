#include "HighScoreBoard.h"
#include <sstream>
#include "Render.h"
#include <fstream>


const SDL_Color HIGHSCOREBOARD_TITLE_COLOR = { 0xF9, 0xF6, 0xF2, 0xFF };
const SDL_Color HIGHSCOREBOARD_POINT_COLOR = { 0xF9, 0xF6, 0xF2, 0xFF };
const SDL_Color HIGHSCOREBOARD_BACKGROUND_COLOR = { 0xBB, 0xAD, 0xA0 };
const char FILE_STORE_HIGHSCORE[] = "data/highscore.txt";

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

    mTextTexture->loadTextureFromText(&highScoreFont, mTitle, HIGHSCOREBOARD_TITLE_COLOR);
    std::stringstream ss;
    ss << mHighScore;
    mHighScoreTexture->loadTextureFromText(&highScoreFont, ss.str().c_str(), HIGHSCOREBOARD_POINT_COLOR);


    mTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
    mTexture->setAsRenderTarget();
    gRender.setDrawColor(HIGHSCOREBOARD_BACKGROUND_COLOR);
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
    mHighScoreTexture->loadTextureFromText(&highScoreFont, ss.str().c_str(), HIGHSCOREBOARD_POINT_COLOR);

    mTexture->setAsRenderTarget();
    gRender.setDrawColor(HIGHSCOREBOARD_BACKGROUND_COLOR);
    gRender.clear();

    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2,
                         (mTexture->getHeight() - mTextTexture->getHeight())/4,
                         NULL);

    mHighScoreTexture->render((mTexture->getWidth() - mHighScoreTexture->getWidth())/2,
                          (mTexture->getHeight() - mHighScoreTexture->getHeight())*3/4,
                          NULL);

    gRender.setRenderTarget(NULL);
    mTexture->render(mPosition.x, mPosition.y);
}

int HighScoreBoard::getHighScore()
{
    return mHighScore;
}

void HighScoreBoard::loadHighScore()
{
        std::ifstream f;
        f.open(FILE_STORE_HIGHSCORE);
        if (f.is_open())
        {
            f >> mHighScore;
        }
        else
        {
            printf("daed file\n");
        }
}

void HighScoreBoard::saveHighScore()
{
        std::ofstream f;
        f.open(FILE_STORE_HIGHSCORE);
        if (f.is_open())
        {
            f << mHighScore;
        }
        else
        {
            printf("daed file\n");
        }
}

void HighScoreBoard::setHighScore(int score)
{
    mHighScore = score;
}
