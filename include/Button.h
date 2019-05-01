#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>
#include <functional>
#include <Texture.h>

class Button
{
    public:
        Button(const char *_text, int _x = 0, int _y = 0, int _w = 120, int _h = 40);
        virtual ~Button();

        void setPosition(int x, int y);
        void setSize(int w, int h);

        void handleEvent(SDL_Event *e);

        bool isInside(int x, int y);

        void setCallBackFunc(std::function<void ()> onClick) { mOnClick = onClick;};

        void render();

    private:
        SDL_Point mPosition;
        int mWidth;
        int mHeight;
        const char *mText;
        Texture *mTexture;
        Texture *mTextTexture;
        std::function<void ()> mOnClick;
};

extern void loadButtonMetadata();

#endif // BUTTON_H
