#include "Font.h"
#include <iostream>

Font::Font()
{
    m_font = NULL;
}

Font::~Font()
{

}

void Font::init(const char* path_to_ttf, int size)
{
    // first, clear the current font
    free();
    // initialize new font
    m_font = TTF_OpenFont(path_to_ttf, size);

    if (!m_font)
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
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = NULL;
    }
}

SDL_Surface *Font::renderText(const char* text, SDL_Color fg_color)
{
    return TTF_RenderText_Blended(this->m_font, text, fg_color);
}
