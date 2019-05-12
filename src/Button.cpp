#include "Button.h"
#include "Font.h"
#include "Texture.h"
#include "Render.h"

static Font btnFont;
const SDL_Color BUTTON_TEXT_COLOR = { 0xF9, 0xF6, 0xF2, 0xFF };
const SDL_Color BUTTON_BACKGROUND_COLOR = { 0x8F, 0x7A, 0x66, 0xFF };
extern void loadButtonMetadata()
{
    const char *fontFile = "Fonts/OpenSans-Bold.ttf";
    btnFont.init(fontFile, 18);
}

Button::Button(const char *_text, int _x, int _y, int _w, int _h)
{
    mPosition.x = _x;
    mPosition.y = _y;
    mWidth = _w;
    mHeight = _h;
    mText = _text;

    mTextTexture = new Texture();
    mTexture = new Texture();

    mTextTexture->loadTextureFromText(&btnFont, mText, BUTTON_TEXT_COLOR);


    mTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
    mTexture->setAsRenderTarget();
    gRender.setDrawColor(BUTTON_BACKGROUND_COLOR);
    gRender.clear();
    mTextTexture->render((mTexture->getWidth() - mTextTexture->getWidth())/2, (mTexture->getHeight() - mTextTexture->getHeight())/2, NULL);

    gRender.setRenderTarget(NULL);
}

Button::~Button()
{
    //dtor
}

void Button::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Button::setSize(int w, int h)
{
    mWidth = w;
    mHeight = h;
}

bool Button::isInside(int x, int y)
{
    if (x < mPosition.x || x > mPosition.x + mWidth || y < mPosition.y || y > mPosition.y + mHeight) return false; else return true;
}

void Button::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (isInside(x, y))
        {
            mOnClick();
        }
    }
}

void Button::render()
{
    mTexture->render(mPosition.x, mPosition.y, NULL);
}


