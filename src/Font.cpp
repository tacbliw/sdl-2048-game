#include "Font.h"
#include <iostream>
#include <stdio.h>

Font::Font()
{
    mFont = NULL;
}

Font::~Font()
{

}

void Font::init(const char* path_to_ttf, int size)
{
    // first, clear the current font
    free();
    // initialize new font
    mFont = TTF_OpenFont(path_to_ttf, size);

    if (!mFont)
    {
        std::cout << "Failed loading font: " << path_to_ttf << std::endl;
        std::cout << "Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        std::cout << "Font loaded: " << path_to_ttf << std::endl;
    }
}

void Font::free()
{
    if (mFont)
    {
        TTF_CloseFont(mFont);
        mFont = NULL;
    }
}

SDL_Surface *Font::renderText(const char* text, SDL_Color fg_color)
{
    return TTF_RenderText_Blended(mFont, text, fg_color);
}
