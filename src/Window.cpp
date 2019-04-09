#include "Window.h"
#include <iostream>

Window::Window(const char *title, int width, int height):
    m_title(title), width(width), height(height)
{
    //ctor
    if (!init())
    {
        closed = true;
        std::cerr << "Can't init window.\n";
    }
}

Window::~Window()
{
    //dtor
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to init SDL.\n";
        return 0;
    }

    window = SDL_CreateWindow(m_title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        std::cerr << "Failed to create window.\n";
        return 0;
    }

    return true;
}
