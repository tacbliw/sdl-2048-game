#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Font.h"

class Texture
{
    public:
        ~Texture() { free(); }
        bool loadTexture(std::string path);
        bool loadTextureFromText(Font *f, const char *text, SDL_Color fgColor);

        void render(int x, int y, SDL_Rect *clip = NULL);

        SDL_Texture* getTexture() { return mTexture; }
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

        void setAsRenderTarget();
        bool createBlankTexture(Uint32 format, int access, int width, int height);
        void setBlendMode();

        void free();
    private:
        SDL_Texture* mTexture;
        int mHeight;
        int mWidth;
};

#endif // TEXTURE_H
