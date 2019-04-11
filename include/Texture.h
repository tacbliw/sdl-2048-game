#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Font.h"

class Texture
{
    public:
        SDL_Texture *loadTexture(std::string path);
        SDL_Texture *loadTextureFromText(Font *f, const char *text, SDL_Color fgColor);

        void render(int x, int y, SDL_Rect *clip = NULL);

        SDL_Texture* getTexture() { return mTexture; }
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

        void setAsRenderTarget(SDL_Texture *texture);
    private:
        SDL_Texture* mTexture;
        int mHeight;
        int mWidth;
};

#endif // TEXTURE_H
