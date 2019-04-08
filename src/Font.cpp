#include "Font.h"
#include <iostream>

Font::Font()
{
    m_font = NULL;
}

Font::~Font()
{

}

Font::init(const char* path_to_ttf, int size)
{
    free();

    m_font = TTF_OpenFont(path_to_ttf, size);

    if (!m_font)
    {
        std::cout << "Load font failed: " << path_to_ttf << endl;
    }
}

Font::free()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = NULL;
    }
}

SDL_Surface Font::renderText(const char* text, SDL_Color fg_color)
{
    return TTF_RenderText_Blended(m_font, text, fg_color);
}
