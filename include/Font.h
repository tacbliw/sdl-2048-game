#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

class Font
{
    public:
        Font();
        virtual ~Font();

        void init(const char *path_to_ttf, int size);
        void free();
        SDL_Surface* renderText(const char* str, SDL_Color fg_color);

    private:
        TTF_Font *mFont;
};

#endif // FONT_H
